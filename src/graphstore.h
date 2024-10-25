#ifndef GRAPHSTORE_H
#define GRAPHSTORE_H

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// The ID of a vertex in the graph.
// This is a positive integer. 0 represents an invalid vertex.
typedef size_t VertexId;

/// Class that stores a graph.
class GraphStore
{
public:
    /// Create a new vertex and return its ID.
    VertexId createVertex();

    /// Create an edge between two vertices.
    /// @param from The ID of the source vertex.
    /// @param to The ID of the destination vertex.
    /// @throws std::runtime_error if either vertex does not exist.
    void createEdge(VertexId from, VertexId to);

    /// Add a label to a vertex.
    /// @param vertex The ID of the vertex.
    /// @param label The label to add to the vertex.
    /// @throws std::runtime_error if the vertex does not exist.
    void addLabel(VertexId vertex, const std::string& label);

    /// Remove a label from a vertex.
    /// @throws std::runtime_error if the vertex does not exist.
    void removeLabel(VertexId vertex, const std::string& label);

    /// Returns the shortest path from one vertex to another. All vertices in the path must have the label given as
    /// parameter. If these is no path between the vertices an empty path is returned.
    /// @param from The ID of the source vertex.
    /// @param to The ID of the destination vertex.
    /// @param label The label that needs to be present on the vertices in the path
    /// @throws std::runtime_error if either vertex does not exist.
    /// @returns A vector containing the IDs of the vertices in the shortest path or an empty path if no such path
    /// exists.
    std::vector<VertexId> shortestPath(VertexId from, VertexId to, const std::string& label) const;

private:
    // We store the vertices in a vector of sets. The position in the vector is the ID of the vertex - 1. We want to
    // avoid 0 being a valid ID. Each set contains the neighbors of the corresponding vertex.
    // Note: at the moment we do not support deletion of vertices. This could be implemented something like std::hive.
    std::vector<std::set<VertexId>> m_vertices;
    // The list of labels. Each label has a set of vertices that have this label.
    // Note: this is optimized for checking whether a vertex has a certain label but listing all labels a node has would
    // be inefficient.
    std::unordered_map<std::string, std::set<VertexId>> m_labels;
};

#endif
