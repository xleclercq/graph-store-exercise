#ifndef GRAPHSTORE_H
#define GRAPHSTORE_H

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

typedef size_t VertexId;

class GraphStore
{
public:
    VertexId createVertex();
    void createEdge(VertexId from, VertexId to);
    void addLabel(VertexId vertex, const std::string& label);
    void removeLabel(VertexId vertex, const std::string& label);

    std::vector<VertexId> shortestPath(VertexId from, VertexId to, const std::string& label) const;

private:
    std::vector<std::set<VertexId>> m_vertices;
    std::unordered_map<std::string, std::set<VertexId>> m_labels;
};

#endif
