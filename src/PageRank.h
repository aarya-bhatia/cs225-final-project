#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "Graph.h"
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <list>
#include <vector>

template <class K, class V>
class PageRank
{
public:
    PageRank(Graph<K, V> *g) : graph(g)
    {
    }

    /**
     * Functor used to compare two (rank,key) pairs.
     */
    struct RankCompare
    {
        /**
         * Returns true if the rank of the first pair is greater than the rank of the second pair. 
         * Otherwise, returns false.
         */
        bool operator()(const std::pair<float, K> &r1, const std::pair<float, K> &r2)
        {
            return r1.first > r2.first;
        }
    };

    /**
     * Initalises the ranks for all vertices. 
     * Sets the inbound edges for all vertices.
     */
    void init();

    /**
     * Prints "key: rank" to std out the for each vertex.
     */
    void print();

    /**
     * Computes the rank of the given vertex for the next iteration of page rank.
     * @param u given vertex
     * @returns next page rank
     */
    float next(Vertex<K, V> *u) const;

    /**
     * Runs the algorithm on the graph.
     * Updates the ranks of the vertices in each cycle of the algorithm.
     * Iteration ends when difference in page ranks of successive iterations < error bound.
     * The formula to update the ranks is below:
     * 
     * Let N = Number of vertices
     * Initial Page Rank = 1/(N)
     * Let ADJ(v): Adjacency List of v
     * Let PR(v): Page rank of v
     * Let DEG(v): Degree of v
     * Let d: damping factor
     * 
     * Then PR(v(t)) = 1 - d + d * [SUM(PR(u(t))/DEG(u)) for all u in ADJ_IN(v)].
     *
     * Stop when PR[v(t+1)] - PR[v(t)] < Error for all vertices
     *
     */
    void solve();

    /**
     * Builds a vector of rank, key pairs from the vertices in the graph after the algorithm computes
     * the final page ranks. Also sorts the vector by rank values and returns it. The keys in the pair
     * help us associate the rank to a vertex in the graph.
     * 
     * @returns a vector of (rank,key) pairs sorted in order from greatest to lowest rank.
     */
    std::vector<std::pair<float, K> > get_ranks() const;

private:
    Graph<K, V> *graph;
    size_t N;

    const float error = 0.005;
    const float dampness = 0.85;
};

#include "PageRank.hpp"

#endif