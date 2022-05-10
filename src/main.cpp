#include "Graph.h"
#include "GraphBuilder.h"
#include "K.h"
#include "util.h"
#include <iostream>

int main()
{
    Graph<std::string, Airport> *g = GraphBuilder::build();

    std::string src;
    std::string dest;

    char in = '0';

    while(in != 'q')
    {
        std::cout << "Enter source airport: ";
        std::cin >> src;

        std::cout << "Enter destination airport: ";
        std::cin >> dest;

        src = util::to_upper_case(src);
        dest = util::to_upper_case(dest); 

        if(src.empty() || src.length() != 3)
        {
            std::cout << "Source airport is invalid...Please enter a 3 letter IATA code" << std::endl;
            continue;
        }

        if(dest.empty() || dest.length() != 3)
        {
            std::cout << "Destination airport is invalid...Please enter a 3 letter IATA code" << std::endl;
            continue;
        }

        g->bfs(src, dest);

        std::vector<std::string> bfs_path = g->path(src, dest); 
        std::cout << "Least connecting flight path by BFS:" << util::to_string(bfs_path) << std::endl;
        
        g->dijkstra(src, dest);

        std::vector<std::string> dijkstra_path = g->path(src, dest); 
        std::cout << "Shortest distance flight path by Dijkkstra:" << util::to_string(dijkstra_path) << std::endl;

        std::cout << "Type q to quit or press any other key to continue.";
        std::cin >> in;
    }

    std::cout << "Program terminating successfully" << std::endl;

    delete g;

    return 0;
}