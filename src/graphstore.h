#ifndef GRAPHSTORE_H
#define GRAPHSTORE_H

#include <set>
#include <vector>

typedef size_t VertexId;

class GraphStore
{
public:
    VertexId createVertex();
    void createEdge(VertexId from, VertexId to);

private:
    std::vector<std::set<VertexId>> m_vertices;
};

#endif
