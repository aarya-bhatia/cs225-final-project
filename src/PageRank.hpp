#ifndef PAGE_RANK_HPP
#define PAGE_RANK_HPP

#include "PageRank.h"

template<class K, class V>
void PageRank<K, V>::init()
{
    N = graph->vertices.size();

    if (N == 0)
    {
        return;
    }

    // Init page rank to 1/N for all vertices

    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        it->second->rank = 1/float(N);
    }

    // Init in_edges for all vertices

    for (auto it = graph->edges.begin(); it != graph->edges.end(); it++)
    {
        Edge<K> *edge = *it;
        Vertex<K, V> *u = graph->vertices[edge->source];
        Vertex<K, V> *v = graph->vertices[edge->destination];
        v->adjIn.push_back(edge);
    }
}

template<class K, class V>
void PageRank<K, V>::print()
{
    for(auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        std::cout << it->first << ":" << it->second->rank << std::endl;
    }

    std::cout << "-------------------------------------------------------" << std::endl;
}

template<class K, class V>
float PageRank<K, V>::next(Vertex<K, V> *u) const
{
    float s = 0;

    for (auto edgeItr = u->adjIn.begin(); edgeItr != u->adjIn.end(); edgeItr++)
    {
        Edge<K> *edge = *edgeItr;
        Vertex<K, V> *v = graph->vertices[edge->source];

        float r = v->rank;

        if (v->degree() > 0)
        {
            r = r / float(v->degree());
        }
        else
        {
            r = r / float(N);
        }

        s += r;
    }

    return 1 - dampness + dampness * s;
}

template<class K, class V>
void PageRank<K, V>::solve()
{
    if (graph == nullptr || graph->empty())
    {
        return;
    }

    init();

    assert(graph->vertices.begin()->second->rank > 0);

    bool stop = false;
    size_t iteration = 0;
    size_t max_it = 1000;

    while (!stop && iteration < max_it)
    {
        stop = true;
        ++iteration;

        for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
        {
            Vertex<K, V> *u = it->second;

            float newRank = next(u);

            if (stop && newRank - u->rank > error)
            {
                stop = false;
            }

            u->rank = newRank;
        }
    }

    std::cout << "Number of Iterations: " << iteration << std::endl;

}

template<class K, class V>
std::vector<std::pair<float, K> > PageRank<K, V>::get_ranks() const
{
    // Fill vertices in vector as (rank,key) pairs.

    std::vector<std::pair<float, K>> ranks;

    if(!graph)
    {
        return ranks;
    }

    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        ranks.push_back(std::make_pair(it->second->rank, it->first));
    }

    // Sort in descending order.
    std::sort(ranks.begin(), ranks.end(), RankCompare());

    return ranks;
}

#endif