#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "Graph.h"
#include "Airport.h"
#include "util.h"
#include "K.h"

#include <string>
#include <iostream>

namespace GraphBuilder
{

    /**
     * @param routes_file csv file with routes data
     * @param airports_file csv file with airports data
     * @return The graph created with given data
     */
    Graph<std::string, Airport> *build(const std::string &routes_file = K::ROUTES_FILE, const std::string &airports_file = K::AIRPORTS_FILE);

    /**
     * Initialises the routes in the given graph from csv file.
     * 
     * @param graph the graph
     * @param filename name of the file
     */
    void init_routes(Graph<std::string, Airport> *graph, const std::string &filename);

    /**
     * Initialises the airports in the given graph from csv file.
     * 
     * @param graph the graph
     * @param filename name of the file
     */
    void init_airports(Graph<std::string, Airport> *graph, const std::string &filename);

    /**
     * Computes and sets the distances of the edges in the graph.
     * 
     * @param graph the graph
     */
    void init_distances(Graph<std::string, Airport> *graph);

}

#endif
