#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vertex.h"

template<class K, class V>
Vertex<K, V>::Vertex(const K &key, const V &value) : key(key), value(value)
{
    parent = nullptr;
    distance = 0;
    visited = false;
    rank = 0;
    adj = std::list<Edge<K> *>();
}

template<class K, class V>
Vertex<K, V>::~Vertex()
{
    // Nothing
}

template<class K, class V>
Vertex<K, V>::Vertex(const Vertex<K, V> &other)
{
    // Warning: The copy constructor for vertex does not copy the parent pointer or the adj list.
    key = other.key;
    value = other.value;
    parent = nullptr;
    distance = other.distance;
    visited = other.visited;
    adj = std::list<Edge<K> *>();
}

template<class K, class V>
unsigned Vertex<K, V>::degree() const
{
    return adj.size();
}

template<class K, class V>
bool Vertex<K, V>::is_adj(Vertex<K, V> *other)
{
    if (other == nullptr)
    {
        return false;
    }

    for (auto edgeItr = adj.begin(); edgeItr != adj.end(); edgeItr++)
    {
        Edge<K> *edge = *edgeItr;

        if (edge->destination == other->key)
        {
            return true;
        }
    }

    return false;
}

template<class K, class V>
Edge<K> *Vertex<K, V>::find_adj(Vertex<K, V> *other)
{
    if (other == nullptr)
    {
        return nullptr;
    }

    for (auto edgeItr = adj.begin(); edgeItr != adj.end(); edgeItr++)
    {
        Edge<K> *edge = *edgeItr;

        if (edge->destination == other->key)
        {
            return edge;
        }
    }

    return nullptr;
}

#endif