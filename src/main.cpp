#include "graphstore.h"
#include <chrono>
#include <iostream>
#include <random>

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

    GraphStore CreateLargeGraphStore(size_t edge_count)
    {
        GraphStore graph_store;

        const size_t vertex_count = 100000;
        for (size_t i = 0; i < vertex_count; ++i)
        {
            VertexId v_id = graph_store.createVertex();
            graph_store.addLabel(v_id, "label 1");
        }

        std::mt19937 rng(0);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000);
        for (size_t i = 0; i < edge_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);
            if (from != to)
            {
                graph_store.createEdge(from, to);
            }
        }

        return graph_store;
    } 

    void SimpleTest1()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2, "label 1");
        PrintPath(path);
    }

    void SimpleTest2()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        graph_store.addLabel(v_id_3, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_3, "label 1");
        PrintPath(path);
    }

    void SimpleTest3()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        graph_store.addLabel(v_id_3, "label 1");

        graph_store.createEdge(v_id_1, v_id_3);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2, "label 1");
        PrintPath(path);
    }

    void SimpleTest4()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        graph_store.addLabel(v_id_3, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);
        graph_store.createEdge(v_id_2, v_id_3);

        const auto path = graph_store.shortestPath(v_id_1, v_id_3, "label 1");
        PrintPath(path);
    }

    void SimpleTest5()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        graph_store.addLabel(v_id_3, "label 1");
        VertexId v_id_4 = graph_store.createVertex();
        graph_store.addLabel(v_id_4, "label 1");
        VertexId v_id_5 = graph_store.createVertex();
        graph_store.addLabel(v_id_5, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);
        graph_store.createEdge(v_id_2, v_id_3);
        graph_store.createEdge(v_id_3, v_id_4);
        graph_store.createEdge(v_id_4, v_id_5);

        const auto path = graph_store.shortestPath(v_id_1, v_id_5, "label 1");
        PrintPath(path);
    }

    void SimpleTest6()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        VertexId v_id_4 = graph_store.createVertex();
        graph_store.addLabel(v_id_4, "label 1");
        VertexId v_id_5 = graph_store.createVertex();
        graph_store.addLabel(v_id_5, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);
        graph_store.createEdge(v_id_2, v_id_3);
        graph_store.createEdge(v_id_3, v_id_4);
        graph_store.createEdge(v_id_4, v_id_5);

        const auto path = graph_store.shortestPath(v_id_1, v_id_5, "label 1");
        PrintPath(path);
    }

    void SimpleTest7()
    {
        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");
        VertexId v_id_3 = graph_store.createVertex();
        VertexId v_id_4 = graph_store.createVertex();
        graph_store.addLabel(v_id_4, "label 1");
        VertexId v_id_5 = graph_store.createVertex();
        graph_store.addLabel(v_id_5, "label 1");

        VertexId v_id_6 = graph_store.createVertex();
        graph_store.addLabel(v_id_6, "label 1");
        VertexId v_id_7 = graph_store.createVertex();
        graph_store.addLabel(v_id_7, "label 1");


        graph_store.createEdge(v_id_1, v_id_2);

        graph_store.createEdge(v_id_2, v_id_3);
        graph_store.createEdge(v_id_3, v_id_4);

        graph_store.createEdge(v_id_2, v_id_6);
        graph_store.createEdge(v_id_6, v_id_7);
        graph_store.createEdge(v_id_7, v_id_4);

        graph_store.createEdge(v_id_4, v_id_5);

        const auto path = graph_store.shortestPath(v_id_1, v_id_5, "label 1");
        PrintPath(path);
    }

    void PerfTest1()
    {
        GraphStore graph_store = CreateLargeGraphStore(100000);

        std::mt19937 rng(0);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000);

        std::chrono::microseconds total_time{0};

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);

            auto t1 = std::chrono::high_resolution_clock::now();
            
            const auto path = graph_store.shortestPath(from, to, "label 1");

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << total_time.count() << "us" << std::endl;
    }

    void PerfTest2()
    {
        GraphStore graph_store = CreateLargeGraphStore(1000000);

        std::mt19937 rng(0);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000);

        std::chrono::microseconds total_time{0};

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);
            
            auto t1 = std::chrono::high_resolution_clock::now();

            const auto path = graph_store.shortestPath(from, to, "label 1");

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << total_time.count() << "us" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        SimpleTest1();
        SimpleTest2();
        SimpleTest3();
        SimpleTest4();
        SimpleTest5();
        SimpleTest6();
        SimpleTest7();
        PerfTest1();
        PerfTest2();
    }
    catch (...)
    {
        std::cerr << "Exception thrown" << std::endl;
    }

    return 0;
}
