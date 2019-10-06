#include "Utils.hpp"
#include "Logger.hpp"

#include <cctype>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>

#include <curl/curl.h>

#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

static size_t readRawData(char *buffer, size_t size, size_t nitems, void *userdata)
{
	std::vector<unsigned char> *data = static_cast<std::vector<unsigned char> *>(userdata);
	std::copy(&buffer[0], &buffer[size * nitems], std::back_inserter(*data));
	return size * nitems;
}

static size_t readHtmlData(char *buffer, size_t size, size_t nitems, void *userdata)
{
	htmlParserCtxtPtr ctxt = static_cast<htmlParserCtxtPtr>(userdata);
	htmlParseChunk(ctxt, buffer, size * nitems, 0);
	return size * nitems;
}

static struct curl_slist *copySlist(struct curl_slist *src)
{
	struct curl_slist *dst = NULL;
	struct curl_slist *tmp;

	while(src) {
		tmp = curl_slist_append(dst, src->data);

		if(!tmp) {
			curl_slist_free_all(dst);
			return NULL;
		}

		dst = tmp;
		src = src->next;
	}

	return dst;
}

static double currencyConvert(double value, double rate)
{
	return value * rate;
}

CURLcode executeWebRequest(std::string url, 
	size_t (*fptr)(char *, size_t, size_t, void *), void *userdata,
	struct curl_slist *headers)
{
	CURLcode res = CURLE_OK;

	CURL *curl = curl_easy_init();

	char errbuf[CURL_ERROR_SIZE] = {0};
	
	struct curl_slist *chunk = copySlist(headers);

	if (!chunk && headers) {
		Logger::warn("Duplication of custom headers failed");
	}

	if (!curl) {
		Logger::error("Easy cURL initialisation failed");

		// cURL itself won't give us an error code, but I guess this is the
		// most appropriate one?
		res = CURLE_FAILED_INIT;
	} else {
		// Need this header so some websites will respond to requests
		chunk = curl_slist_append(
			chunk,
			"User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:59.0) Gecko/20100101 Firefox/59.0"
		);
		
		if (!chunk) {
			Logger::warn("Unable to allocate HTTP headers");
		}

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		// follow redirects
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// configure callback for parsing web page
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, userdata);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fptr);

		// register pointer to buffer for human readable error messages
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

		// set target URL
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		
		// execute the request
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);	    
	}

	if (res != CURLE_OK) {
		size_t len = strlen(errbuf);

		if(len) {
			Logger::error(errbuf);
		} else {
			Logger::error(curl_easy_strerror(res));
		}
	}

	curl_slist_free_all(chunk);

	return res;
}

std::string hash(std::string s)
{
	return std::to_string(std::hash<std::string>{}(s));
}

std::string lowerCase(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string upperCase(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

std::string getFirstRegexMatch(std::string s, std::regex r)
{
	std::smatch matches;
	
	if (std::regex_search(s, matches, r)) {
		return matches[0];
	}

	return "";
}

xmlXPathObjectPtr xpathSearchDom(xmlDocPtr doc, const xmlChar *query)
{
	xmlXPathObjectPtr xpathObj;
	xmlXPathContextPtr xpathCtx;

	xpathCtx = xmlXPathNewContext(doc);

	if(!xpathCtx) {
		Logger::error("Unable to create new XPath context");
		xpathObj = NULL;
	} else {
		xpathObj = xmlXPathEvalExpression(query, xpathCtx);
		xmlXPathFreeContext(xpathCtx);
	}

	return xpathObj;
}

void xpathSearchIterateDom(xmlDocPtr doc, const xmlChar *query,
	std::function<bool(xmlNodePtr)> fn)
{
	int size;

	xmlXPathObjectPtr result = xpathSearchDom(doc, query);

	if (result) {
		xmlNodeSetPtr nodes = result->nodesetval;

		size = (nodes) ? nodes->nodeNr : 0;

		for(int i = 0; i < size; ++i) {
			if(!fn(nodes->nodeTab[i])) {
				break;
			}
		}

		xmlXPathFreeObject(result);
	}
}

std::string getXmlAttribute(xmlNodePtr ptr, std::string attrName)
{
	std::string link = "";

	if (ptr != NULL) {

		xmlAttr *attrs = ptr->properties;
		
		while (attrs) {
			if (attrName.compare((char *) attrs->name) == 0) {
				if (attrs->children != NULL) {
					link = (char *) attrs->children->content;
				}

				break;
			}

			attrs = attrs->next;
		}
	}

	return link;
}

xmlDocPtr fetchWebPage(std::string url, struct curl_slist *headers)
{
	CURLcode res;

	xmlDocPtr doc = NULL;

	// create an HTML parser
	htmlParserCtxtPtr ctxt;

	ctxt = htmlCreatePushParserCtxt(
		NULL, NULL, NULL, 0, NULL, XML_CHAR_ENCODING_NONE
	);
		
	if (!ctxt) {
		Logger::error("Unable to create new HTML parser context");
	} else {
		// ignore any errors/poor formatting in the HTML
		htmlCtxtUseOptions(
			ctxt, 
			HTML_PARSE_NOBLANKS
			| HTML_PARSE_NOERROR
			| HTML_PARSE_NOWARNING
			| HTML_PARSE_NONET
		);

		res = executeWebRequest(url, readHtmlData, ctxt, headers);

		if (res == CURLE_OK) {
			// get the resulting XML document
			doc = ctxt->myDoc;	
		}

		// free the parser
		htmlFreeParserCtxt(ctxt);	
	}

	return doc;
}

std::vector<unsigned char> fetchRawData(std::string url, struct curl_slist *headers)
{
	std::vector<unsigned char> data;

	executeWebRequest(url, readRawData, &data, headers);

	return data;
}

double sterlingToEuro(double sterling)
{
	return currencyConvert(sterling, STERLING_EURO_CONVERSION_RATE);
}

double dollarToEuro(double dollar)
{
	return currencyConvert(dollar, DOLLAR_EURO_CONVERSION_RATE);
}

double applyVat(double price)
{
	return price + (price * IRELAND_VAT);
}

std::string getBasename(std::string path)
{
	size_t found = path.find_last_of("/");

	return (found == std::string::npos)? path : path.substr(found + 1);
}

int saveRawDataFile(std::string fname, std::vector<unsigned char> data)
{
	int res = 1;

	std::ofstream imageFile(
		"data/" + fname,
		std::ios::out | std::ofstream::binary
	);
			
	if (!imageFile.is_open()) {
		Logger::warn("Unable to open data file \"", fname, "\"");
		res = 0;
	} else {
		std::copy(
			data.begin(),
			data.end(),
			std::ostreambuf_iterator<char>(imageFile)
		);
		
		imageFile.close();
	}

	return res;
}