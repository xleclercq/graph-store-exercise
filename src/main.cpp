#include "graphstore.h"
#include <iostream>

namespace
{
    void PrintPath(const std::vector<VertexId>& path)
    {
        for (const auto& vertex : path)
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        VertexId v_id_2 = graph_store.createVertex();

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2);
        PrintPath(path);
    }
    catch (...)
    {
        std::cerr << "Exceptiom thrown" << std::endl;
    }

    return 0;
}
