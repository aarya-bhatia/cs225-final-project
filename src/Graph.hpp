#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Graph.h"
#include "util.h"
#include <queue>
#include <iostream>
#include <assert.h>
#include <functional> /* For std::greater */

template<class K, class V>
Graph<K, V>::Graph()
{
    // Do Nothing
}

template<class K, class V>
Graph<K, V>::~Graph()
{
    _destroy();
}

template<class K, class V>
Graph<K, V>::Graph(const Graph &g)
{
    _copy(g);
}

template<class K, class V>
Graph<K, V> &Graph<K, V>::operator=(const Graph &g)
{
    if(this != &g)
    {
        _destroy();
        _copy(g);
    }

    return *this;
}

template<class K, class V>
bool Graph<K, V>::has_vertex(const K &key) const
{
    return vertices.find(key) != vertices.end();
}

template<class K, class V>
void Graph<K, V>::create_edge(const K &src, const K &dest)
{
    if(has_vertex(src) && has_vertex(dest))
    {
        Vertex<K,V> *u = vertices[src];
        Edge<K> *e = new Edge<K>(src, dest);
        u->adj.push_back(e);

        edges.push_back(e);
    }
}

template<class K, class V>
void Graph<K, V>::create_vertex(const K &key, const V &value)
{
    Vertex<K,V> *u = new Vertex<K,V>(key, value);
    vertices[key] = u;
}


template<class K, class V>
void Graph<K,V>::bfs(const K& src, const K& dest)
{
    if(!has_vertex(src) || !has_vertex(dest)) 
    {
        return;
    }

    for(auto it = vertices.begin(); it != vertices.end(); it++)
    {
        Vertex<K, V> *u = it->second;
        u->distance = INT_MAX;
        u->parent = nullptr;
        u->visited = false;
    }

    std::queue<Vertex<K, V> *> q;

    vertices[src]->distance = 0.0;
    q.push(vertices[src]);

    while(!q.empty() && !vertices[dest]->visited)
    {
        Vertex<K,V> *u = q.front();
        q.pop();

        for(auto edgeItr = u->adj.begin(); edgeItr != u->adj.end(); edgeItr++)
        {
            Edge<K> *edge = *edgeItr;
            Vertex<K,V> *v = vertices[edge->destination];

            if(!v->visited)
            {
                v->visited = true;

                if(v->distance > u->distance + 1)
                {
                    v->distance = u->distance + 1;
                    v->parent = u;
                }

                q.push(v);
            }
        }

        u->visited = true;
    }
}

template<class K, class V>
void Graph<K,V>::dijkstra(const K& src, const K& dest)
{
    if(!has_vertex(src) || !has_vertex(dest)) 
    {
        return;
    }

    for(auto it = vertices.begin(); it != vertices.end(); it++)
    {
        Vertex<K, V> *u = it->second;
        u->distance = INT_MAX;
        u->parent = nullptr;
        u->visited = false;
    }

    typedef std::pair<float, Vertex<K,V> *> vpair;
    
    std::priority_queue<vpair, std::vector<vpair>, std::greater<vpair> > q;

    vertices[src]->distance = 0.0;
    q.push(std::make_pair(0.0, vertices[src]));

    while(!q.empty() && !vertices[dest]->visited)
    {
        vpair current = q.top();
        q.pop();

        Vertex<K,V> *u = current.second;

        /* We might get duplicate vertices in the queue. */
        if(u->visited) 
        {
            continue;
        }

        for(auto edgeItr = u->adj.begin(); edgeItr != u->adj.end(); edgeItr++)
        {
            Edge<K> *edge = *edgeItr;
            Vertex<K, V> *v = vertices[edge->destination];

            assert(vertices[edge->source] == u);

            /* We check if found shorter path than before from u to v */
            if(!v->visited)
            {
                if(v->distance > u->distance + edge->distance)
                {
                    v->distance = u->distance + edge->distance;
                    v->parent = u;
                }

                q.push(std::make_pair(v->distance, v));
            }
        }

        u->visited = true;
    }
}

template<class K, class V>
std::vector<K> Graph<K,V>::path(const K&src, const K&dest)
{
    if(!has_vertex(src) || !has_vertex(dest))
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << "Failed to find path from <" << src << "> to <" << dest << ">" << std::endl;
        return std::vector<K>();
    }

    std::vector<K> forward_path;
    std::stack<K> backward_path;

    Vertex<K,V> *current = vertices[dest];

    while(current != nullptr)
    {
        backward_path.push(current->key);
        current = current->parent;
    }

    while(!backward_path.empty())
    {
        forward_path.push_back(backward_path.top());
        backward_path.pop();
    }

    return forward_path;
}

template<class K, class V>
float Graph<K, V>::path_length(std::vector<K> &path)
{
    float length = 0.0;

    if(path.empty())
    {
        return length;
    }

    for(size_t i = 0; i < path.size() - 1; i++)
    {
        Vertex<K,V> *u = vertices[path[i]];
        Vertex<K,V> *v = vertices[path[i+1]];

        if(!u || !v)
        {
            continue;
        }

        Edge<K> *e = u->find_adj(v);

        if(e != nullptr)
        {
            length += e->distance;
        }
    }

    return length;
}

template<class K, class V>
void Graph<K, V>::_destroy()
{
    /* Delete edges */
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        delete (*it);
        *it = nullptr;
    }

    /* Delete vertices */
    for(auto it = vertices.begin(); it != vertices.end(); it++)
    {
        delete it->second;
        it->second = nullptr;
    }
}

template<class K, class V>
void Graph<K, V>::_copy(const Graph<K, V> &g)
{
    for(auto it = g.vertices.begin(); it != g.vertices.end(); it++)
    {
        create_vertex(it->first, it->second->value);
    }

    for(auto it = g.edges.begin(); it != g.edges.end(); it++)
    {
        create_edge((*it)->source, (*it)->destination);
    }
}

/**
 * Builds a transpose graph by flipping the direction of all the edges.
 * @returns transposed graph
 */
template <class K, class V>
Graph<K, V> *Graph<K, V>::transpose() const
{
    Graph<K, V> *g = new Graph<K, V>();

    /* Copy all vertices from this graph to new graph */
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        g->create_vertex(it->first, it->second->value);
    }

    /* For every edge (u,v) in this graph, create edge (v,u) in new graph */
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        g->create_edge((*it)->destination, (*it)->source);
    }

    return g;
}

#endif