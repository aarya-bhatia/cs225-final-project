#ifndef SCC_HPP
#define SCC_HPP

#include "SCC.h"

template <class K, class V>
std::vector<std::vector<K> > SCC<K, V>::get_components() const 
{
    return components;
}

template <class K, class V>
Graph<K, V> *SCC<K, V>::get_graph() const 
{ 
    return graph; 
}

template <class K, class V>
void SCC<K, V>::set_graph(Graph<K, V> *g)
{
    graph = g;
}


/**
 * Finds and stores the strongly connected components
 */
template <class K, class V>
void SCC<K, V>::scc()
{
    if (!graph)
    {
        return;
    }

    std::stack<Vertex<K, V> *> s;

    // Mark all vertices as unvisited for first DFS
    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        it->second->visited = false;
    }

    // Fill vertices in stack according to their finish times
    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        Vertex<K, V> *u = it->second;

        if (!u->visited)
        {
            dfs_finish_times(graph, u, s);
        }
    }

    Graph<K, V> *gt = graph->transpose();

    // Mark all vertices as unvisited for second DFS
    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        it->second->visited = false;
    }

    components.clear();

    std::vector<K> component;

    // Do second dfs in the order defined by stack on transpose graph.
    while (!s.empty())
    {
        Vertex<K, V> *u = s.top();
        s.pop();

        // Find this vertex in the transpose graph
        Vertex<K, V> *v = gt->vertices[u->key];

        assert(v->key == u->key);

        // A scc is found each time we pop unvisited vertex.
        if (!v->visited)
        {
            if (!component.empty())
            {
                components.push_back(component);
            }

            component.clear();

            // Run dfs from this vertex on transpose graph
            dfs(gt, v, component);
        }
    }

    // Last scc
    if (!component.empty())
    {
        components.push_back(component);
    }

    // Delete transpose graph
    delete gt;
}

/**
 * Recursive dfs helper function
 */
template <class K, class V>
void SCC<K, V>::dfs(Graph<K, V> *g, Vertex<K, V> *u, std::vector<K> &component)
{
    if (!g)
    {
        return;
    }

    u->visited = true;

    component.push_back(u->key);

    for (auto it = u->adj.begin(); it != u->adj.end(); it++)
    {
        Vertex<K, V> *v = g->vertices[(*it)->destination];

        if (!v->visited)
        {
            dfs(g, v, component);
        }
    }
}

/**
 * Fills stack with vertices in the order of finish times in the DFS traversal.
 */
template <class K, class V>
void SCC<K, V>::dfs_finish_times(Graph<K, V> *g, Vertex<K, V> *u, std::stack<Vertex<K, V> *> &s)
{
    if (!g)
    {
        return;
    }

    u->visited = true;

    for (auto it = u->adj.begin(); it != u->adj.end(); it++)
    {
        Vertex<K, V> *v = g->vertices[(*it)->destination];

        if (!v->visited)
        {
            dfs_finish_times(g, v, s);
        }
    }

    s.push(u);
}

/**
 * @param u vertex in a SCC
 * @returns the representative vertex of the SCC.
 */
template <class K, class V>
Vertex<K, V> *SCC<K, V>::find_root(Vertex<K, V> *u)
{
    if (!u->parent)
    {
        return u;
    }

    return find_root(u->parent);
}

template <class K, class V>
Graph<K, V> *SCC<K, V>::build_condensed_graph()
{
    if (!graph)
    {
        return nullptr;
    }

    Graph<K, V> *g = new Graph<K, V>(); // The condensed graph

    for (auto it = graph->vertices.begin(); it != graph->vertices.end(); it++)
    {
        it->second->parent = nullptr;
    }

    for (auto it = components.begin(); it != components.end(); it++)
    {
        std::vector<K> &component = *it;

        /* Set the first member of each component as the representative of that component */

        Vertex<K, V> *parent = graph->vertices[component.front()];

        for (auto compIt = component.begin(); compIt != component.end(); compIt++)
        {
            if (*compIt != parent->key)
                graph->vertices[*compIt]->parent = parent;
        }

        /* Create vertex for representative element */

        g->create_vertex(parent->key, parent->value);
    }

    /*
     * Create edges in condensed graph by taking all edges in each component
     * and joining them by the representative vertex of its endpoints.
     */
    for (auto it = graph->edges.begin(); it != graph->edges.end(); it++)
    {
        Edge<K> *edge = *it;

        Vertex<K, V> *u0 = graph->vertices[edge->source];
        Vertex<K, V> *v0 = graph->vertices[edge->destination];

        Vertex<K, V> *u1 = find_root(u0);
        Vertex<K, V> *v1 = find_root(v0);

        Vertex<K, V> *u = g->vertices[u1->key];
        Vertex<K, V> *v = g->vertices[v1->key];

        if (u != v && !u->is_adj(v))
        {
            g->create_edge(u->key, v->key);
        }
    }

    return g;
}

#endif