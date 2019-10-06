#ifndef __SERVICE_API__
#define __SERVICE_API__

#include "Van.hpp"
#include "KnowledgeGraph.hpp"

#include <string>
#include <vector>
#include <functional>

class ServiceApi
{
public:
	virtual ~ServiceApi() {};
	
	virtual void fetchVanData(KnowledgeGraph &knowledgeGraph) = 0;

	virtual std::string getServiceName() = 0;

	virtual std::string getServiceUrl() = 0;
};

#endif