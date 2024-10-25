#include "graphstore.h"
#include <map>

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

    VertexId cheapestVertex(const std::set<VertexId>& open_set, const std::map<VertexId, int>& f_score)
    {
        VertexId cheapest_vertex;
        int current_lowest_score = std::numeric_limits<int>::max();
        for (VertexId vertex : open_set)
        {
            int current_score = Cost(f_score, vertex);
            if (current_score < current_lowest_score)
            {
                cheapest_vertex = vertex;
                current_lowest_score = current_score;
            }
        }
        return cheapest_vertex;
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
    // TODO check for existence

    m_vertices[from-1].insert(to);
}

std::vector<VertexId> GraphStore::shortestPath(VertexId from, VertexId to) const
{
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    std::set<VertexId> open_set = {from};
    
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
    std::map<VertexId, VertexId> came_from;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    std::map<VertexId, int> g_score;
    g_score[from] = 0;

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    std::map<VertexId, int> f_score;
    f_score[from] = 0;

    while (!open_set.empty())
    {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        VertexId current_vertex = cheapestVertex(open_set, f_score);
        if (current_vertex == to)
        {
            return ReconstructPath(came_from, current_vertex);
        }
        
        open_set.erase(current_vertex);
        for (const VertexId& neighbour : m_vertices[current_vertex-1])
        {
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_g_score is the distance from start to the neighbor through current
            int tentative_g_score = Cost(g_score, current_vertex) + 1;
            if (tentative_g_score < Cost(g_score, neighbour))
            {
                // This path to neighbor is better than any previous one. Record it!
                came_from[neighbour] = current_vertex;
                g_score[neighbour] = tentative_g_score;
                f_score[neighbour] = tentative_g_score;
                open_set.insert(neighbour);
            }
        }
    }

    // Open set is empty but goal was never reached
    return std::vector<VertexId>();
}
