#include "graphstore.h"
#include <limits>
#include <map>
#include <queue>
#include <stdexcept>
#include <iostream>

namespace
{
    // The wikipedia algorithm we refer to in shortestPath fills some of the sets with infinity. This is wasteful as
    // we'd have to add all the vertices even the ones we'll never visit. Just assume that if it's not in the set its
    // score is infinity.
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
        
    // Class used to implement a heap with a std::set. This is used in the A* algorithm and helps us identify the vertex
    // with the lowest score efficiently.
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
    if ((vertex - 1) > m_vertices.size())
    {
        throw std::runtime_error("Vertex does not exist");
    }

    m_labels[label].insert(vertex);
}

void GraphStore::removeLabel(VertexId vertex, const std::string& label)
{
    if ((vertex - 1) > m_vertices.size())
    {
        throw std::runtime_error("Vertex does not exist");
    }

    m_labels[label].erase(vertex);
    if (m_labels[label].empty())
    {
        m_labels.erase(label);
    }
}

std::vector<VertexId> GraphStore::shortestPath(VertexId from, VertexId to, const std::string& label) const
{
    // This is an implementation of the A* algorithm as described in https://en.wikipedia.org/wiki/A*_search_algorithm
    // With h(vertex) always 0 and d(vertex_1, vertex_2) always 1 since our graph doesn't have a weight on the edges.
    // Essentially this disable the heuristic part of the A* algorithm.

    if (((from - 1) > m_vertices.size()) || ((to - 1) > m_vertices.size()))
    {
        throw std::runtime_error("Vertex does not exist");
    }

    if (m_labels.at(label).count(from) == 0)
    {
        return std::vector<VertexId>();
    }
    
    // This as heap implementation based on std::set. We use a custom class, VertexAndScore, with a custom operator< to
    // make sure the element with the lowest score is at the beginning of the set.
    std::set<VertexAndScore> open_set;
    open_set.insert(VertexAndScore(from, 0));
    
    std::map<VertexId, VertexId> came_from;

    std::map<VertexId, int> g_score;
    g_score[from] = 0;

    while (!open_set.empty())
    {
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

            int tentative_g_score = Cost(g_score, current_vertex) + 1;
            if (tentative_g_score < Cost(g_score, neighbour))
            {
                came_from[neighbour] = current_vertex;
                g_score[neighbour] = tentative_g_score;
                open_set.insert(VertexAndScore(neighbour, tentative_g_score));
            }
        }
    }

    return std::vector<VertexId>();
}
