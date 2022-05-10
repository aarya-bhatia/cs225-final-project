#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.h"
#include <list>
#include <utility>

template <class K, class V>
class Vertex
{
public:

    Vertex(const K &key, const V &value);

    Vertex(const Vertex<K, V> &other);
    
    ~Vertex();
    
    /**
     * @return The number of outgoing edges from this vertex
     */
    unsigned degree() const;

    /**
     * @param other a vertex
     * @return checks if this vertex is adjacent to the other vertex, i.e. the edge (this, other) exists
     */
    bool is_adj(Vertex<K, V> *other);
    
    /**
     * Finds an edge that contains other vertex as endpoint.
     * @param other the vertex
     * @return the edge containing the vertices or nullptr if none found.
     */
    Edge<K> *find_adj(Vertex<K, V> *other);

    K key;
    V value;
    
    Vertex<K, V> *parent;
    float distance;
    bool visited;
    float rank;

    std::list<Edge<K> *> adj; // Edges that start from this vertex and end at another vertex.
    std::list<Edge<K> *> adjIn; // Edges that start at another vertex and end at this vertex.

};

#include "Vertex.hpp"

#endif
