#ifndef __SCRAPER_APP_HPP__
#define __SCRAPER_APP_HPP__

#include "ServiceApi.hpp"
#include "PluginHandle.hpp"

#include <vector>

class ScraperApp
{
public:
	enum InitResultCode 
	{ 
		SUCCESS, 
		UNKNOWN_FLAG, 
		BAD_FLAG_ARGUMENT, 
		USAGE_INFORMATION_PRINTED ,
		BAD_FILE_NAME,
	};

	ScraperApp();
	
	~ScraperApp();
	
	ScraperApp::InitResultCode parseArgs(int argc, char *argv[]);

	void addServiceApi(ServiceApi *api);

	void scrape();

	ScraperApp::InitResultCode initialise();

	void usage(const char *progname);

	static int run(int argc, char *argv[]);

private:
	std::vector<ServiceApi *> apiEndpoints;

	std::vector<PluginHandle *> plugins;

	std::string confFile;
};

#endif