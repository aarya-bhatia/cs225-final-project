/**
 * Strongly connected components of given directed graph
 */

#ifndef SCC_H
#define SCC_H

#include "Graph.h"
#include <map>

template<class K, class V>
class SCC
{
    public:
        SCC(Graph<K, V> *g)
        {
            graph = g;
        }

        /**
         * @return Get the SCCs of the graph
         */
        std::vector<std::vector<K> > get_components() const;

        Graph<K, V> *get_graph() const;

        void set_graph(Graph<K, V> *g);

        /**
         * Finds strongly connected components 
         */
        void scc();

        /**
         * Depth first search traversal from given vertex.
         * Adds the path to the component which stores the vertices in the current scc.
         * @param g graph to execute dfs on
         * @param u current vertex
         * @param component contains the vertices in the current strongly connected component
         */
        void dfs(Graph<K, V> *g, Vertex<K, V> *u, std::vector<K> &component);

        /** 
         * DFS Traversal on the given graph starting from given vertex.
         * Stores the vertices in the order they were last seen to stack.
         * @param g the graph
         * @param u current vertex
         * @param s the stack
         */
        void dfs_finish_times(Graph<K, V> *g, Vertex<K, V> *u, std::stack<Vertex<K, V> *> &s);

        /**
         * Builds a condensed graph by shrink each strongly connected component to a single vertex
         * and choosing one vertex in each component as a representative.
         */
        Graph<K, V> *build_condensed_graph();

        /**
         * @param u vertex in a SCC
         * @returns the representative vertex of the SCC.
         */
        Vertex<K, V> *find_root(Vertex<K, V> *u);

    private:

        Graph<K, V> *graph; /* The graph */

        std::vector<std::vector<K> > components; /* the strongly connected components */

};

#include "SCC.hpp"

#endif