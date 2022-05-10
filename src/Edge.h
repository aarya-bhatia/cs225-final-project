#ifndef EDGE_H
#define EDGE_H

template<class K>
class Edge
{
    public:

        Edge(const K &src, const K &dest): source(src), destination(dest), distance(0.0)
        {
        }

        ~Edge()
        {
        }

        K source;
        K destination;
        float distance;
};

#endif