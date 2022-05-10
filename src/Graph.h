#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include <string>
#include <limits.h> /* For INT_MAX */
#include <utility> /* For std::pair, std::make_pair */
#include <vector>
#include <stack>
#include <unordered_map>
#include <assert.h>

/**
 * This class represents the graph of our model.
 */
template<class K, class V>
class Graph
{
    public:
        Graph();
        ~Graph();
        Graph(const Graph &g);
        Graph<K, V> &operator=(const Graph &g);

        std::unordered_map<K, Vertex<K,V> *> vertices;
        std::vector<Edge<K> *> edges;

        bool has_vertex(const K &key) const;
        void create_edge(const K &src, const K &dest);
        void create_vertex(const K &key, const V &value = V());
        float path_length(std::vector<K> &path);

        bool empty() const { return vertices.empty(); }

        /**
         * Follows the backward path from each vertex to its parent vertex
         * till reaches end. Then reverses this path to get the actual path.
         * @param src start vertex key
         * @param dest end vertex key
         * @return path from src to dest vertex
         */
        std::vector<K> path(const K &src, const K &dest);

        /**
         * Does a Breadth first search traversal on graph to find the shortest path 
         * from start to end vertex with least connecting flight. 
         * To do this let all edges cost be 1.
         * @param src start vertex
         * @param dest end vertex
         */
        void bfs(const K& src, const K& dest);
        
        /**
         * Runs Dijkstra's algorithm on this graph
         * to find the shortest path from src to dest vertex.
         * @param src start vertex
         * @param dest end vertex
         */
        void dijkstra(const K& src, const K& dest);

        /**
         * Builds a transpose graph by flipping the direction of all the edges.
         * @returns transposed graph
         */
        Graph<K, V> *transpose() const;

    private:
        void _destroy();
        void _copy(const Graph<K, V> &g);

};

#include "Graph.hpp"

#endif