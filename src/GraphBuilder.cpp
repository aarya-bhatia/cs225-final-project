#include "GraphBuilder.h"
#include "Vertex.h"
#include "util.h"
#include <utility>

namespace GraphBuilder
{

    /**
     * @param routes_file csv file with routes data
     * @param airports_file csv file with airports data
     * @return The graph created with given data
     */
    Graph<std::string, Airport> *build(const std::string &routes_file, const std::string &airports_file)
    {
        Graph<std::string, Airport> *graph = new Graph<std::string, Airport>();

        init_routes(graph, routes_file);
        init_airports(graph, airports_file);
        init_distances(graph);

        std::cout << "Initialised " << graph->vertices.size() << " vertices." << std::endl;

        return graph;
    }

    /**
     * Initialises the routes in the given graph from csv file.
     * 
     * @param graph the graph
     * @param filename name of the file
     */
    void init_routes(Graph<std::string, Airport> *graph, const std::string &filename)
    {
        std::vector<std::vector<std::string>> rows = util::parse_csv_file(filename);

        for (auto it = rows.begin(); it != rows.end(); it++)
        {
            const std::vector<std::string> &columns = *it;

            std::string source_airport = columns[K::ROUTES_SOURCE_AIRPORT];
            std::string destination_airport = columns[K::ROUTES_DESTINATION_AIRPORT];

            /* We must create airport if routes are initialised before the airports */

            if (graph->vertices.find(source_airport) == graph->vertices.end())
            {
                graph->create_vertex(source_airport, Airport());
            }

            if (graph->vertices.find(destination_airport) == graph->vertices.end())
            {
                graph->create_vertex(destination_airport, Airport());
            }

            graph->create_edge(source_airport, destination_airport);
        }
    }

    /**
     * Initialises the airports in the given graph from csv file.
     * 
     * @param graph the graph
     * @param filename name of the file
     */
    void init_airports(Graph<std::string, Airport> *graph, const std::string &filename)
    {
        std::vector<std::vector<std::string>> rows = util::parse_csv_file(filename);

        for (auto it = rows.begin(); it != rows.end(); it++)
        {
            const std::vector<std::string> &columns = *it;

            /* access the required columns by index */

            std::string name = columns[K::AIRPORT_NAME];
            std::string city = columns[K::AIRPORT_CITY];
            std::string country = columns[K::AIRPORT_COUNTRY];
            std::string iata = columns[K::AIRPORT_IATA];
            std::string icao = columns[K::AIRPORT_ICAO];

            /* convert the string coordinates to float */

            float latitude = atof(columns[K::AIRPORT_LATITUDE].c_str());
            float longitude = atof(columns[K::AIRPORT_LONGITUDE].c_str());

            Airport *airport = nullptr;

            /* Check if airport has been initialised before, check if it was created with IATA or ICAO code. */
            /* If airport has not been initialised before by either, then create the airport */

            if (graph->vertices.find(iata) != graph->vertices.end())
            {
                airport = &graph->vertices[iata]->value;
            }
            else if (graph->vertices.find(icao) != graph->vertices.end())
            {
                airport = &graph->vertices[icao]->value;
            }
            else if (iata.length() == 3)
            {
                graph->create_vertex(iata, Airport());
                airport = &graph->vertices[iata]->value;
            }
            else if (icao.length() == 4)
            {
                graph->create_vertex(icao, Airport());
                airport = &graph->vertices[icao]->value;
            }
            else
            {
                std::cout << __LINE__ << ": Airport code is missing or invalid [IATA: " << iata << "] [ICAO: " << icao << "]" << std::endl;
            }

            /* Update all fields for airport as required */

            if (airport != nullptr)
            {
                airport->name = name;
                airport->city = city;
                airport->country = country;
                airport->latitude = latitude;
                airport->longitude = longitude;
            }
        }
    }

    /**
     * Computes and sets the distances of the edges in the graph.
     * 
     * @param graph the graph
     */
    void init_distances(Graph<std::string, Airport> *graph)
    {
        for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
        {
            Vertex<std::string, Airport> *u = it->second;

            float lat1 = u->value.latitude;
            float lon1 = u->value.longitude;

            for (auto edgeItr = u->adj.begin(); edgeItr != u->adj.end(); edgeItr++)
            {
                Edge<std::string> *edge = *edgeItr;
                Vertex<std::string, Airport> *v = graph->vertices[edge->destination];

                float lat2 = v->value.latitude;
                float lon2 = v->value.longitude;

                edge->distance = util::distance(lat1, lon1, lat2, lon2);
            }
        }
    }

}