#include "graphstore.h"
#include <iostream>

namespace
{
    void PrintPath(const std::vector<VertexId>& path)
    {
        if (path.empty())
        {
            std::cout << "No path found" << std::endl;
            return;
        }

        for (const auto& vertex : path)
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    void SimpleTest1()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        VertexId v_id_2 = graph_store.createVertex();

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2);
        PrintPath(path);
    }

    void SimpleTest2()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        VertexId v_id_2 = graph_store.createVertex();
        VertexId v_id_3 = graph_store.createVertex();

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_3);
        PrintPath(path);
    }

    void SimpleTest3()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        VertexId v_id_2 = graph_store.createVertex();
        VertexId v_id_3 = graph_store.createVertex();

        graph_store.createEdge(v_id_1, v_id_3);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2);
        PrintPath(path);
    }
}

int main(int argc, char* argv[])
{
    try
    {
        SimpleTest1();
        SimpleTest2();
        SimpleTest3();
    }
    catch (...)
    {
        std::cerr << "Exceptiom thrown" << std::endl;
    }

    return 0;
}
