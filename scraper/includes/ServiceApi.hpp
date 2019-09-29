#ifndef __SERVICE_API__
#define __SERVICE_API__

#include "Van.hpp"

#include <string>
#include <vector>

class ServiceApi
{
public:
	virtual ~ServiceApi() {};
	
	virtual std::vector<Van> fetchVanData() = 0;

	virtual std::string getServiceName() = 0;

	virtual std::string getServiceUrl() = 0;
};

#endif