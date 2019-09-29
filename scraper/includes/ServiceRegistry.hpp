#ifndef __SERVICE_REGISTRY_HPP__
#define __SERVICE_REGISTRY_HPP__

#include "ServiceApi.hpp"

#include <map>
#include <string>

typedef ServiceApi* (*ServiceMaker)();
typedef void (*ServiceDestroyer)(ServiceApi *);

class ServiceRegistry
{
private:
	static std::map<std::string, ServiceMaker> serviceMakers;

	static std::map<std::string, ServiceDestroyer> serviceDestroyers;

public:
	static void registerServiceMaker(std::string name, ServiceMaker serviceMaker);

	static void registerServiceDestroyer(std::string name, ServiceDestroyer serviceDestroyer);

	static std::map<std::string, ServiceMaker> getMakers();

	static std::map<std::string, ServiceDestroyer> getDestroyers();
};

#endif