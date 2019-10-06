#ifndef __KNOWLEDGE_GRAPH_HPP__
#define __KNOWLEDGE_GRAPH_HPP__

#include "Van.hpp"

#include <string>
#include <redland.h>

class KnowledgeGraph
{
private:
	librdf_world   *world;
	librdf_model   *rdf_model;
	librdf_storage *rdf_storage;

public:
	KnowledgeGraph();

	~KnowledgeGraph();

	int loadGraphFromFile(std::string fname, std::string format = "turtle");

	int saveGraphToFile(std::string fname, std::string format = "turtle");

	void addVanToGraph(Van &van);
};

#endif