#include "ServiceRegistry.hpp"

// initialize empty map
std::map<std::string, ServiceMaker> ServiceRegistry::serviceMakers = {};

std::map<std::string, ServiceDestroyer> ServiceRegistry::serviceDestroyers = {};

void ServiceRegistry::registerServiceMaker(std::string name, ServiceMaker serviceMaker)
{
	ServiceRegistry::serviceMakers[name] = serviceMaker;
}

void ServiceRegistry::registerServiceDestroyer(std::string name, ServiceDestroyer serviceDestroyer)
{
	ServiceRegistry::serviceDestroyers[name] = serviceDestroyer;
}

std::map<std::string, ServiceMaker> ServiceRegistry::getMakers()
{
	return serviceMakers;
}

std::map<std::string, ServiceDestroyer> ServiceRegistry::getDestroyers()
{
	return serviceDestroyers;
}