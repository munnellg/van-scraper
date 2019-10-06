#include "KnowledgeGraph.hpp"

#include "Logger.hpp"

#include <cstdio> // FILE, fopen, fclose

KnowledgeGraph::KnowledgeGraph()
{
	this->world = librdf_new_world();

	if (!this->world) {
		throw std::bad_alloc();
	}

	librdf_world_open(this->world);

	this->rdf_storage = librdf_new_storage(this->world, "memory", "test", NULL);
	
	if(!this->rdf_storage) {
		librdf_free_world(this->world);
		throw std::bad_alloc();
	}

	this->rdf_model = librdf_new_model(this->world, this->rdf_storage, NULL);

	if (!this->rdf_model) {
		librdf_free_storage(rdf_storage);
		librdf_free_world(this->world);
		throw std::bad_alloc();
	}
}

KnowledgeGraph::~KnowledgeGraph()
{
	librdf_free_model(this->rdf_model);
	librdf_free_storage(rdf_storage);
	librdf_free_world(this->world);
}

int KnowledgeGraph::loadGraphFromFile(std::string fname, std::string format)
{
	FILE *f;
	librdf_parser *rdf_parser;

	int res = 0;

	f = fopen(fname.c_str(), "r");

	if (!f) {
		Logger::error("Failed to open file \"", fname, "\"");
		res = 1;
	} else {
		rdf_parser = librdf_new_parser(this->world, format.c_str(), NULL, NULL);

		if (rdf_parser == NULL) {
			Logger::error(
				"Failed to load \"", fname, "\". Unrecognised format \"",
				format, "\""
			);

			res = 1; // non-zero result so we know an error occurred
		} else {
			librdf_uri *base_uri = librdf_new_uri(this->world, (const unsigned char *) "https://www.vanmonster.com/en-ie/");
			
			res = librdf_parser_parse_file_handle_into_model(
				rdf_parser, f, 0, base_uri, this->rdf_model
			);

			librdf_free_parser(rdf_parser);

			librdf_free_uri(base_uri);
		}

		fclose(f);
	}

	return res;
}

int KnowledgeGraph::saveGraphToFile(std::string fname, std::string format)
{
	int res = 0;

	FILE *f = fopen(fname.c_str(), "w");
	
	librdf_serializer* serializer;

	if (!f) {
		Logger::error("Failed to open \"", fname, "\" for writing");
		res = 1;		
	} else {
		serializer = librdf_new_serializer(this->world, format.c_str(), NULL, NULL);
		
		librdf_serializer_serialize_model_to_file_handle(serializer, f, NULL, this->rdf_model);
  		
  		librdf_free_serializer(serializer);
  
		fclose(f);
	}

	return res;
}

void KnowledgeGraph::addVanToGraph(Van &van)
{
	librdf_statement *statement;
	
	librdf_node *subject = librdf_new_node_from_uri_string(this->world, (const unsigned char*) van.getAdvertisementUrl().c_str());
	librdf_node *predicate = librdf_new_node_from_uri_string(this->world, (const unsigned char*) "http://example.com/make");
	librdf_node *object = librdf_new_node_from_literal(this->world, (const unsigned char*) van.getMake().c_str(), NULL, 0);

	statement = librdf_new_statement_from_nodes(
		this->world, subject, predicate, object
	);

	librdf_model_add_statement(this->rdf_model, statement);

	predicate = librdf_new_node_from_uri_string(this->world, (const unsigned char*) "http://example.com/model");
	object = librdf_new_node_from_literal(this->world, (const unsigned char*) van.getModel().c_str(), NULL, 0);

	statement = librdf_new_statement_from_nodes(
		this->world, subject, predicate, object
	);

	librdf_model_add_statement(this->rdf_model, statement);

	librdf_free_statement(statement);
}