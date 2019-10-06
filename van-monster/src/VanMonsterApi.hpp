#ifndef __VAN_MONSTER_API__
#define __VAN_MONSTER_API__

#include "ServiceApi.hpp"

#include <Enums.hpp>

#include <map>
#include <regex>
#include <vector>
#include <string>
#include <libxml/tree.h>
#include <libxml/xpath.h>

class VanMonsterApi : public ServiceApi
{
private:
	static const std::string SITE_ROOT;
	static const std::string API_ENDPOINT;
	static const std::string SERVICE_NAME;

	static const xmlChar* PRICE_XPATH;
	static const xmlChar* TITLE_XPATH;
	static const xmlChar* FEATURES_XPATH;
	static const xmlChar* VIEW_AD_BUTTON_XPATH;
	static const xmlChar* NEXT_PAGE_BUTTON_XPATH;
	static const xmlChar* IMAGES_XPATH;

	static const std::regex YEAR_REGEX;
	static const std::regex HEIGHT_REGEX;
	static const std::regex LENGTH_REGEX;

	static const std::string LABEL_MILEAGE;
	static const std::string LABEL_MPG;
	static const std::string LABEL_CO2;
	static const std::string LABEL_BODY;
	static const std::string LABEL_ENGINE_SIZE;
	static const std::string LABEL_COLOUR;
	static const std::string LABEL_ABS;
	static const std::string LABEL_AIR_CON;
	static const std::string LABEL_AIRBAGS;
	static const std::string LABEL_BLUETOOTH;
	static const std::string LABEL_BULKHEAD;
	static const std::string LABEL_CD_PLAYER;
	static const std::string LABEL_ELECTRIC_MIRRORS;
	static const std::string LABEL_ELECTRIC_WINDOWS;
	static const std::string LABEL_HEATED_SEATS;
	static const std::string LABEL_PLY_LINING;
	static const std::string LABEL_POWER_STEERING;
	static const std::string LABEL_CRUISE_CONTROL;
	static const std::string LABEL_PAYLOAD_KG;
	static const std::string LABEL_LENGTH;
	static const std::string LABEL_TRANSMISSION;
	static const std::string LABEL_FUEL_TYPE;

	static const std::map<std::string, std::vector<std::string>> MAKE_TO_MODEL;

	bool isLastPage(xmlDocPtr doc);

	void updateFeature(Van &van, std::string label, std::string value);

	void generateUuid(Van &van);

	void extractFeatures(xmlDocPtr doc, Van &van);

	void extractPrice(xmlDocPtr doc, Van &van);

	void extractTitleData(xmlDocPtr doc, Van &van);

	void extractImages(xmlDocPtr doc);

	Van extractVanData(xmlNodePtr ptr);

	void processResults(xmlNodeSetPtr nodes, KnowledgeGraph &knowledgeGraph);

public:
	VanMonsterApi();

	~VanMonsterApi();

	void fetchVanData(KnowledgeGraph &knowledgeGraph);

	std::string getServiceName();

	std::string getServiceUrl();

	// Allow the RegisterService class to access private attributes
	friend class RegisterService;
};

#endif