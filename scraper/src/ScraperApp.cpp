#include "Logger.hpp"
#include "ScraperApp.hpp"
#include "ServiceRegistry.hpp"

#include <cstring>    // strcmp
#include <fstream>    // ifstream
#include <sstream>    // istringstream
#include <iostream>   // cout, string, EXIT_FAILURE, EXIT_SUCCESS

#include <curl/curl.h>

ScraperApp::ScraperApp()
{
	this->confFile = "scrape.conf";
}
	
ScraperApp::~ScraperApp()
{
	std::map<std::string, ServiceDestroyer> serviceDestroyers = ServiceRegistry::getDestroyers();
	
	// delete all service endpoints
	for (auto it = this->apiEndpoints.begin(); it != this->apiEndpoints.end(); it++) {
		ServiceApi *api = *it;
		
		std::map<std::string, ServiceDestroyer>::iterator map_it;
		
		map_it = serviceDestroyers.find(api->getServiceName());

		if (map_it == serviceDestroyers.end()) {
			Logger::error("No destructor found for \"", api->getServiceName(), "\" : Possible memory leak");
		} else {
			map_it->second(api);
		}
	}

	// close all opened plugins
	for (auto it = this->plugins.begin(); it != this->plugins.end(); it++) {
		(*it)->close();
		delete (*it);
	}
}

ScraperApp::InitResultCode ScraperApp::parseArgs(int argc, char *argv[])
{
	ScraperApp::InitResultCode result = ScraperApp::InitResultCode::SUCCESS;

	for (int i = 1; i < argc && result == InitResultCode::SUCCESS; i++) {
		// arguments with a leading '-' are flags
		if (argv[i][0] == '-') {
			if (strcmp(argv[i], "-h") == 0) { // help flag
				usage(argv[0]);
				result = InitResultCode::USAGE_INFORMATION_PRINTED;
			}
			else if (strcmp(argv[i], "-l") == 0) { // log level flag
				if (++i >= argc) { // ensure log level was passed an argument
					Logger::error("\"-l\" flag expects numerical argument.");
					result = InitResultCode::BAD_FLAG_ARGUMENT;
				} else {
					// attempt to parse log level argument
					int level;
					
					std::istringstream iss(argv[i]);	

					iss >> level;

					if (iss.fail() 
						|| level < static_cast<int>(Logger::LogLevel::DEBUG) 
						|| level > static_cast<int>(Logger::LogLevel::NONE)) {
						Logger::error(
							"Invalid argument to \"-l\" : \"",
							argv[i],
							"\""
						);

						result = InitResultCode::BAD_FLAG_ARGUMENT;
					} else {
						// if all went well, set the log level
						Logger::logLevel = static_cast<Logger::LogLevel>(level);
					}
				}
			} else if (strcmp(argv[i], "-c") == 0) { // conf file flag
				if (++i >= argc) { // ensure log level was passed an argument
					Logger::error("\"-c\" flag expects argument.");
					result = InitResultCode::BAD_FLAG_ARGUMENT;
				} else {
					this->confFile = std::string(argv[i]);
				}
			} else { // unknown flag was passed to the program
				Logger::error("Unrecognised flag \"", argv[i], "\"");
				result = InitResultCode::UNKNOWN_FLAG;
			}
		}
	}

	return result;
}

void ScraperApp::addServiceApi(ServiceApi *api)
{
	Logger::info("Registering ", api->getServiceName(), " for scraping.");
	
	this->apiEndpoints.push_back(api);
}

void ScraperApp::scrape()
{
	this->knowledgeGraph.loadGraphFromFile("test.ttl");

	for (auto it = this->apiEndpoints.begin(); it != this->apiEndpoints.end(); it++) {
		Logger::info(
			"Scraping ", (*it)->getServiceName(), " at ", (*it)->getServiceUrl()
		);

		(*it)->fetchVanData(this->knowledgeGraph);
	}

	this->knowledgeGraph.saveGraphToFile("test.ttl");
}

ScraperApp::InitResultCode ScraperApp::initialise()
{
	// Open the configuration file and load the paths to the plugins that should
	// be used
	std::ifstream in(this->confFile);

	if (!in.is_open()) {
		Logger::error("Failed to open ", this->confFile);
		return InitResultCode::BAD_FILE_NAME;
	}

	// One plugin per line of the config file
	std::string pluginName;

	while (std::getline(in, pluginName)) {
		this->plugins.push_back(new PluginHandle(pluginName));
	}

	in.close();

	// Open the plugins that were found in the config file.
	// This will register the respective constructors in the service registry
	for (auto it = this->plugins.begin(); it != this->plugins.end(); it++) {
		PluginHandle *ph = *it;

		if (!ph->open()) {
			Logger::error(ph->lastError());
		}
	}

	// Create scrapers from the service registry
	std::map<std::string, ServiceMaker> serviceMakers = ServiceRegistry::getMakers();

	std::map<std::string, ServiceMaker>::iterator it;

	for (it = serviceMakers.begin(); it != serviceMakers.end(); it++ ) {
		Logger::info("Creating ", it->first, " scraper");
		this->apiEndpoints.push_back(it->second());
	}

	return ScraperApp::InitResultCode::SUCCESS;
}

void ScraperApp::usage(const char *progname)
{
	std::cout << progname << " [options]" << std::endl;
	std::cout << std::endl;
	std::cout << "options" << std::endl;
	std::cout << "\t-h" << std::endl;
	std::cout << "\t\tDisplay this help message." << std::endl;
	std::cout << "\t-l N" << std::endl;
	std::cout << "\t\tSet log level. N=0 displays all messages. "
		"N=4 disables logging." << std::endl;
	std::cout << "\t-c FILE" << std::endl;
	std::cout << "\t\tUse FILE for initialisation parameters." << std::endl;
}

int ScraperApp::run(int argc, char *argv[])
{
	ScraperApp scraper;

	// test for failed initialisation
	if (scraper.parseArgs(argc, argv) != ScraperApp::InitResultCode::SUCCESS) {
		return EXIT_FAILURE;
	}

	if (scraper.initialise() != ScraperApp::InitResultCode::SUCCESS) {
		return EXIT_FAILURE;
	}
	
	int result = EXIT_SUCCESS;

	scraper.scrape();

	return result;
}