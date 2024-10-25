#include "graphstore.h"

VertexId GraphStore::createVertex()
{
    VertexId new_id = (m_vertices.size() + 1);
    m_vertices.emplace_back(std::set<VertexId>());
    return new_id;
}

void GraphStore::createEdge(VertexId from, VertexId to)
{
    // TODO check for existence

    m_vertices[from].insert(to);
}
