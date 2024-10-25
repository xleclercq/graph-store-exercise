#include "graphstore.h"
#include <map>
#include <queue>
#include <stdexcept>
#include <iostream>

namespace
{
    int Cost(const std::map<VertexId, int>& scores, VertexId vertex)
    {
        if (scores.count(vertex) > 0)
        {
            return scores.at(vertex);
        }
        return std::numeric_limits<int>::max();
    }

    std::vector<VertexId> ReconstructPath(const std::map<VertexId, VertexId>& cameFrom, VertexId current)
    {
        std::vector<VertexId> total_path = {current};
        while (cameFrom.count(current) > 0)
        {
            current = cameFrom.at(current);
            total_path.insert(total_path.begin(), current);
        }
        return total_path;
    }

    class VertexAndScore
    {
    public:
        VertexAndScore(VertexId vertex, int score) : m_vertex(vertex), m_score(score) {};

        bool operator<(const VertexAndScore& other) const
        {
            if (m_score < other.m_score)
            {
                return true;
            }
            else if (m_score > other.m_score)
            {
                return false;
            }
            else
            {
                return m_vertex < other.m_vertex;
            }
        }

        VertexId m_vertex;
        int m_score;
    };

    VertexId cheapestVertex(std::set<VertexAndScore>& open_set)
    {
        VertexId top = open_set.begin()->m_vertex;
        open_set.erase(open_set.begin());
        return top;
    }
}

VertexId GraphStore::createVertex()
{
    VertexId new_id = (m_vertices.size() + 1);
    m_vertices.emplace_back(std::set<VertexId>());
    return new_id;
}

void GraphStore::createEdge(VertexId from, VertexId to)
{
    if (((from - 1) > m_vertices.size()) || ((to - 1) > m_vertices.size()))
    {
        throw std::runtime_error("Vertex does not exist");
    }

    m_vertices[from-1].insert(to);
}

void GraphStore::addLabel(VertexId vertex, const std::string& label)
{
    m_labels[label].insert(vertex);
}

void GraphStore::removeLabel(VertexId vertex, const std::string& label)
{
    m_labels[label].erase(vertex);
}

std::vector<VertexId> GraphStore::shortestPath(VertexId from, VertexId to, const std::string& label) const
{
    if (m_labels.at(label).count(from) == 0)
    {
        return std::vector<VertexId>();
    }
    
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    std::set<VertexAndScore> open_set;
    open_set.insert(VertexAndScore(from, 0));
    
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
    std::map<VertexId, VertexId> came_from;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    std::map<VertexId, int> g_score;
    g_score[from] = 0;

    while (!open_set.empty())
    {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        VertexId current_vertex = cheapestVertex(open_set);
        if (current_vertex == to)
        {
            return ReconstructPath(came_from, current_vertex);
        }
        
        for (const VertexId& neighbour : m_vertices[current_vertex-1])
        {
            if (m_labels.at(label).count(neighbour) == 0)
            {
                continue;
            }

            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_g_score is the distance from start to the neighbor through current
            int tentative_g_score = Cost(g_score, current_vertex) + 1;
            if (tentative_g_score < Cost(g_score, neighbour))
            {
                // This path to neighbor is better than any previous one. Record it!
                came_from[neighbour] = current_vertex;
                g_score[neighbour] = tentative_g_score;
                open_set.insert(VertexAndScore(neighbour, tentative_g_score));
            }
        }
    }

    // Open set is empty but goal was never reached
    return std::vector<VertexId>();
}
