#ifndef __UTILS_H__
#define __UTILS_H__

#include <regex>
#include <string>

#include <libxml/tree.h>
#include <libxml/xpath.h>

// exchange rate 28/September/2019
const double STERLING_EURO_CONVERSION_RATE = 1.12332111;

// exchange rate 29/September/2019
const double DOLLAR_EURO_CONVERSION_RATE = 0.913751039;

const double IRELAND_VAT = 0.23;

std::string hash(std::string s);

std::string lowerCase(std::string s);

std::string upperCase(std::string s);

std::string getFirstRegexMatch(std::string s, std::regex r);

xmlXPathObjectPtr xpathSearchDom(xmlDocPtr doc, const xmlChar *query);

void xpathSearchIterateDom(xmlDocPtr doc, const xmlChar *query,
	std::function<bool(xmlNodePtr)> fn);

std::string getXmlAttribute(xmlNodePtr ptr, std::string attrName);

xmlDocPtr fetchWebPage(std::string url, struct curl_slist *headers = NULL);

double sterlingToEuro(double sterling);

double dollarToEuro(double dollar);

double applyVat(double price);

#endif