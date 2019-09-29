#include "VanMonsterApi.hpp"

#include <Van.hpp>
#include <Utils.hpp>
#include <Logger.hpp>
#include <ServiceRegistry.hpp>

#include <cstdio>
#include <iostream>
#include <algorithm>    // std::remove_if

#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

const std::string VanMonsterApi::SITE_ROOT    = "https://www.vanmonster.com";
const std::string VanMonsterApi::API_ENDPOINT = "https://www.vanmonster.com/en-ie/find-a-van?page=";
const std::string VanMonsterApi::SERVICE_NAME = "Van Monster";

const xmlChar* VanMonsterApi::PRICE_XPATH            = (xmlChar *) "//div[contains(concat(' ', normalize-space(@class), ' '), ' price ')]//span[contains(concat(' ', normalize-space(@class), ' '), ' green ')]";
const xmlChar* VanMonsterApi::TITLE_XPATH            = (xmlChar *) "//h1[contains(concat(' ', normalize-space(@class), ' '), ' vehicle-title ')]";
const xmlChar* VanMonsterApi::VIEW_AD_BUTTON_XPATH   = (xmlChar *) "//div[contains(concat(' ', normalize-space(@class), ' '), ' view-button ')]//a";
const xmlChar* VanMonsterApi::NEXT_PAGE_BUTTON_XPATH = (xmlChar *) "//div[contains(concat(' ', normalize-space(@class), ' '), ' page-select ')]//a[contains(concat(' ', normalize-space(@class), ' '), ' next ')]";
const xmlChar* VanMonsterApi::FEATURES_XPATH         = (xmlChar *) "//div[contains(concat(' ', normalize-space(@class), ' '), ' vehicle-spec-list ')]";

const std::regex VanMonsterApi::YEAR_REGEX("^[1-9][0-9][0-9][0-9]");
const std::regex VanMonsterApi::HEIGHT_REGEX("[ 1-4]H[1-3][L ]");
const std::regex VanMonsterApi::LENGTH_REGEX("[ 1-3]L[1-4][H ]");

const std::string VanMonsterApi::LABEL_MILEAGE          = "Mileage";
const std::string VanMonsterApi::LABEL_MPG              = "MPG combined";
const std::string VanMonsterApi::LABEL_CO2              = "CO2 (g/km)";
const std::string VanMonsterApi::LABEL_BODY             = "Body";
const std::string VanMonsterApi::LABEL_ENGINE_SIZE      = "Engine size";
const std::string VanMonsterApi::LABEL_COLOUR           = "Colour";
const std::string VanMonsterApi::LABEL_ABS              = "ABS";
const std::string VanMonsterApi::LABEL_AIR_CON          = "Air conditioning";
const std::string VanMonsterApi::LABEL_AIRBAGS          = "Airbags";
const std::string VanMonsterApi::LABEL_BLUETOOTH        = "Bluetooth";
const std::string VanMonsterApi::LABEL_BULKHEAD         = "Bulkhead";
const std::string VanMonsterApi::LABEL_CD_PLAYER        = "CD player";
const std::string VanMonsterApi::LABEL_ELECTRIC_MIRRORS = "Electric mirrors";
const std::string VanMonsterApi::LABEL_ELECTRIC_WINDOWS = "Electric windows";
const std::string VanMonsterApi::LABEL_HEATED_SEATS     = "Heated seats";
const std::string VanMonsterApi::LABEL_PLY_LINING       = "Ply lining";
const std::string VanMonsterApi::LABEL_POWER_STEERING   = "Power steering";
const std::string VanMonsterApi::LABEL_CRUISE_CONTROL   = "Cruise control";
const std::string VanMonsterApi::LABEL_PAYLOAD_KG       = "Payload (kg)*";
const std::string VanMonsterApi::LABEL_LENGTH           = "Total length (mm)";
const std::string VanMonsterApi::LABEL_TRANSMISSION     = "Transmission";
const std::string VanMonsterApi::LABEL_FUEL_TYPE        = "Fuel type";

const std::map<std::string, std::vector<std::string>> VanMonsterApi::MAKE_TO_MODEL = {
	{ "Fiat",       { "Ducato" } },
	{ "Ford",       { "Fiesta", "Transit", "Kuga" } },
	{ "Mercedes",   { "A Class", "Sprinter" } },
	{ "Mitsubishi", { "Outlander" } },
	{ "Peugeot",    { "Boxer", "Partner" } },
	{ "Renault",    { "Master", "Kangoo", "Trafic" } },
	{ "Toyota",     { "Auris" } },
	{ "Vauxhall",   { "Combo", "Vivaro", "Movano" } },
	{ "Volkswagen", { "Caddy", "Crafter", "Transporter" } }
};

VanMonsterApi::VanMonsterApi()
{

}

VanMonsterApi::~VanMonsterApi()
{

}

void VanMonsterApi::updateFeature(Van &van, std::string label, std::string value)
{
	try {
		if      (label == LABEL_MILEAGE)          { van.setMileage(std::stod(value)); }
		else if (label == LABEL_MPG)              { van.setMilesPerGallon(std::stod(value)); }
		else if (label == LABEL_CO2)              { van.setEmissions(std::stod(value)); }
		else if (label == LABEL_BODY)             { van.setBodyType(value); }
		else if (label == LABEL_ENGINE_SIZE)      { van.setEngineSize(std::stod(value)); }
		else if (label == LABEL_COLOUR)           { van.setColour(value); }
		else if (label == LABEL_ABS)              { van.setHasAbs(stringToIsPresent(value)); }
		else if (label == LABEL_AIR_CON)          { van.setHasAirConditioning(stringToIsPresent(value)); }
		else if (label == LABEL_AIRBAGS)          { van.setHasAirbags(stringToIsPresent(value)); }
		else if (label == LABEL_BLUETOOTH)        { van.setHasBluetooth(stringToIsPresent(value)); }
		else if (label == LABEL_BULKHEAD)         { van.setHasBulkhead(stringToIsPresent(value)); }
		else if (label == LABEL_CD_PLAYER)        { van.setHasCdPlayer(stringToIsPresent(value)); }
		else if (label == LABEL_ELECTRIC_MIRRORS) { van.setHasElectricMirrors(stringToIsPresent(value)); }
		else if (label == LABEL_ELECTRIC_WINDOWS) { van.setHasElectricWindows(stringToIsPresent(value)); }
		else if (label == LABEL_HEATED_SEATS)     { van.setHasHeatedSeats(stringToIsPresent(value)); }
		else if (label == LABEL_PLY_LINING)       { van.setHasPlyLining(stringToIsPresent(value)); }
		else if (label == LABEL_POWER_STEERING)   { van.setHasPowerSteering(stringToIsPresent(value)); }
		else if (label == LABEL_CRUISE_CONTROL)   { van.setHasCruiseControl(stringToIsPresent(value)); }
		else if (label == LABEL_PAYLOAD_KG)       { van.setPayload(std::stod(value)); }
		else if (label == LABEL_LENGTH)           { van.setLength(std::stod(value)); }
		else if (label == LABEL_TRANSMISSION)     { van.setTransmission(stringToTransmission(value)); }
		else if (label == LABEL_FUEL_TYPE)        { van.setFuelType(stringToFuelType(value)); }
		else {
			Logger::warn(VanMonsterApi::SERVICE_NAME, " : Unknown feature \"", label, "\"");
		}
	} catch (const std::invalid_argument& ia) {
		Logger::warn(VanMonsterApi::SERVICE_NAME, "Invalid argument for \"",
			label, "\" = \"", value, "\""
		);
	}
}

void VanMonsterApi::extractFeatures(xmlDocPtr doc, Van &van)
{
	// count so we know that we found a few features
	int identifiedFeatures = 0;

	xpathSearchIterateDom(doc, FEATURES_XPATH,
		[&](xmlNodePtr node) {
			identifiedFeatures++;

			// TODO: Has to be a better way to find the correct children
			xmlNodePtr labelNode = node->children->next;
			xmlNodePtr valueNode = node->children->next->next->next;
			
			std::string label((char *) labelNode->children->content);
			std::string value((char *) valueNode->children->content);

			updateFeature(van, label, value);

			return true; // continue processing results
		}
	);

	if (identifiedFeatures <= 0) {
		Logger::warn(VanMonsterApi::SERVICE_NAME, ": No features found");
	}
}

void VanMonsterApi::extractPrice(xmlDocPtr doc, Van &van)
{
	// make sure we find at least one title
	int identifiedPrices = 0;

	xpathSearchIterateDom(doc, PRICE_XPATH,
		[&](xmlNodePtr node) {
			double price;

			identifiedPrices++;

			std::string priceText((char *) node->children->content);

			// this is a former price -- skip it
			if (priceText.find("Was") != std::string::npos) {
				// keep iterating over results
				return true;
			}
			
			// Hold on to the original price text to figure out currency later
			std::string priceDigits(priceText);

			// remove all characters that are not digits
			priceDigits.erase(
				std::remove_if(
					priceDigits.begin(),
					priceDigits.end(),
					[](char c) { return !std::isdigit(c) && c != '.'; }
				),
				priceText.end()
			);

			// attempt conversion from string to double
			try {
				price = std::stod(priceDigits);
			} catch (const std::invalid_argument& ia) {
				Logger::warn(VanMonsterApi::SERVICE_NAME,
					"Unable to parse price", priceText
				);

				// keep iterating over results
				return true;
			}

			// check if we need to convert currencies
			if (priceText.rfind("£") != std::string::npos) {
				price = sterlingToEuro(price);
			} else if (priceText.rfind("$") != std::string::npos) {
				price = dollarToEuro(price);
			}

			// store resulting price in cents
			van.setPrice(applyVat(price) * 100);

			// we can find multiple prices, but if a price passes all checks
			// above then we're done. We've found a good one. Probably.
			return false;
		}
	);

	if (identifiedPrices <= 0) {
		Logger::warn(VanMonsterApi::SERVICE_NAME, ": No prices found");
	}
}

void VanMonsterApi::extractTitleData(xmlDocPtr doc, Van &van)
{
	int identifiedTitles = 0;

	std::string titleText;
	std::string registrationText;

	xpathSearchIterateDom(doc, TITLE_XPATH,
		[&](xmlNodePtr node) {
			identifiedTitles++;

			// TODO: Should be a better, safer way to find children
			xmlNodePtr detailsNode = nodes->nodeTab[0]->children;
			xmlNodePtr registrationNode = nodes->nodeTab[0]->children->next;

			titleText = (char *) detailsNode->children->content;
			registrationText = (char *) registrationNode->children->content;

			van.setAdTitle(titleText + " " + registrationText);

			return true;
		}
	);

	// There should be only one title on the page
	if (identifiedTitles < 1) {
		Logger::warn(VanMonsterApi::SERVICE_NAME, " : Found no titles");
		return;
	} else if (identifiedTitles > 1) {
		Logger::warn(VanMonsterApi::SERVICE_NAME, " : Found ", identifiedTitles,
			" titles. 1 expected. Using last title found.");
	} 

	// Identify make and model of the van from the title
	for (auto const& it : MAKE_TO_MODEL) {
		if(titleText.find(it.first) != std::string::npos) {
			van.setMake(it.first);
			
			for (auto const& itt : it.second) {
				if(titleText.find(itt) != std::string::npos) {
					van.setModel(itt);
					break;
				}
			}

			break;
		}
	}
	
	std::string year;
	if ((year = getFirstRegexMatch(titleText, YEAR_REGEX)) != "") {
		van.setYear(std::stoi(year));
	}

	std::string heightCode;
	if ((heightCode = getFirstRegexMatch(titleText, HEIGHT_REGEX)) != "") {
		van.setHeightCode(stringToHeightCode(heightCode.substr(1,2)));
	}

	std::string lengthCode;
	if ((lengthCode = getFirstRegexMatch(titleText, LENGTH_REGEX)) != "") {
		van.setLengthCode(stringToLengthCode(lengthCode.substr(1,2)));
	}
}

bool VanMonsterApi::isLastPage(xmlDocPtr doc)
{
	int size;

	bool result = true;

	xmlXPathObjectPtr nextArrow = xpathSearchDom(doc, NEXT_PAGE_BUTTON_XPATH);

	if (nextArrow) {
		xmlNodeSetPtr nodes = nextArrow->nodesetval;

		size = (nodes) ? nodes->nodeNr : 0;

		result = (size <= 0);

		xmlXPathFreeObject(nextArrow);
	}

	return result;
}

void VanMonsterApi::generateUuid(Van &van)
{
	van.setUuid(hash(van.getAdTitle()));
}

Van VanMonsterApi::extractVanData(xmlNodePtr ptr)
{
	Van van;
	
	std::string advertisementUrl = VanMonsterApi::SITE_ROOT + getXmlAttribute(ptr, "href");

	van.setAdvertisementUrl(advertisementUrl);

	Logger::info(VanMonsterApi::SERVICE_NAME, " : Fetching ", advertisementUrl);

	xmlDocPtr advertisement = fetchWebPage(advertisementUrl);

	extractFeatures(advertisement, van);

	extractPrice(advertisement, van);	

	extractTitleData(advertisement, van);

	generateUuid(van);

	xmlFreeDoc(advertisement);

	return van;
}

void VanMonsterApi::processResults(xmlNodeSetPtr nodes, std::vector<Van> &vans)
{
	int size;
	
	size = (nodes) ? nodes->nodeNr : 0;
	
	for(int i = 0; i < size; ++i) {
		if(nodes->nodeTab[i]->type != XML_ELEMENT_NODE) {
			continue;
		}
		
		vans.push_back(extractVanData(nodes->nodeTab[i]));
	}
}

std::vector<Van> VanMonsterApi::fetchVanData()
{
	std::vector<Van> result;

	xmlDocPtr doc;
    xmlXPathObjectPtr xpathObj; 

    bool done = false;

    for (int pageNum = 1; !done ; pageNum++) {

    	std::cerr << pageNum << std::endl;

    	doc = fetchWebPage(VanMonsterApi::API_ENDPOINT + std::to_string(pageNum));

		xpathObj = xpathSearchDom(doc, VIEW_AD_BUTTON_XPATH);
		if(xpathObj != NULL) {
			processResults(xpathObj->nodesetval, result);

			// free the xpath result nodes
			xmlXPathFreeObject(xpathObj);
		}

		// done = isLastPage(doc);
		done = true;

		// free the document when we are done
		xmlFreeDoc(doc);
    }

    return result;
}

std::string VanMonsterApi::getServiceName()
{
	return VanMonsterApi::SERVICE_NAME;
}

std::string VanMonsterApi::getServiceUrl()
{
	return VanMonsterApi::API_ENDPOINT;
}

extern "C"
{
	ServiceApi *makeService()
	{
		return new VanMonsterApi();
	}

	void destroyService(ServiceApi *api)
	{
		VanMonsterApi *vm = static_cast<VanMonsterApi *>(api);
		delete vm;
	}
}

class RegisterService
{
public:
	RegisterService()
	{
		ServiceRegistry::registerServiceMaker(VanMonsterApi::SERVICE_NAME, &makeService);
		ServiceRegistry::registerServiceDestroyer(VanMonsterApi::SERVICE_NAME, &destroyService);
	}
};

// when this object is initialized, it will register service with global
// service registry
RegisterService rs;