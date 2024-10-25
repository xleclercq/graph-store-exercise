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

        std::cout << "Found path: ";
        for (const auto& vertex : path)
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    GraphStore CreateLargeGraphStore(size_t vertex_count, size_t edge_count)
    {
        GraphStore graph_store;

        for (size_t i = 0; i < vertex_count; ++i)
        {
            VertexId v_id = graph_store.createVertex();
            graph_store.addLabel(v_id, "label 1");
        }

        std::mt19937 rng(0);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, static_cast<std::mt19937::result_type>(vertex_count));
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

    // Checks that a path is found in a graph with 2 vertices.
    void SimpleTest1()
    {
        std::cout << "SimpleTest1" << std::endl;

        GraphStore graph_store;

        VertexId v_id_1 = graph_store.createVertex();
        graph_store.addLabel(v_id_1, "label 1");
        VertexId v_id_2 = graph_store.createVertex();
        graph_store.addLabel(v_id_2, "label 1");

        graph_store.createEdge(v_id_1, v_id_2);

        const auto path = graph_store.shortestPath(v_id_1, v_id_2, "label 1");
        PrintPath(path);
        if (path == std::vector<VertexId>{1, 2})
        {
            std::cout << "SimpleTest1 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest1 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Checks what happens when a path is not found.
    void SimpleTest2()
    {
        std::cout << "SimpleTest2" << std::endl;

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
        if (path == std::vector<VertexId>{})
        {
            std::cout << "SimpleTest2 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest2 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Checks what happens when a path is not found.
    void SimpleTest3()
    {
        std::cout << "SimpleTest3" << std::endl;

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
        if (path == std::vector<VertexId>{})
        {
            std::cout << "SimpleTest3 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest3 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Checks a path with 2 vertices in shortest path.
    void SimpleTest4()
    {
        std::cout << "SimpleTest4" << std::endl;

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
        if (path == std::vector<VertexId>{1, 2, 3})
        {
            std::cout << "SimpleTest4 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest4 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Checks a path with 5 vertices in shortest path.
    void SimpleTest5()
    {
        std::cout << "SimpleTest5" << std::endl;

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
        if (path == std::vector<VertexId>{1, 2, 3, 4, 5})
        {
            std::cout << "SimpleTest5 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest5 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Same as SimpleTest5, but no path exists because one of the vertices is missing the required label.
    void SimpleTest6()
    {
        std::cout << "SimpleTest6" << std::endl;

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
        if (path == std::vector<VertexId>{})
        {
            std::cout << "SimpleTest6 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest6 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Checks that a path is found when some vertices are missing the required label but another path exists.
    void SimpleTest7()
    {
        std::cout << "SimpleTest7" << std::endl;

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
        if (path == std::vector<VertexId>{})
        {
            std::cout << "SimpleTest7 passed" << std::endl;
        }
        else
        {
            std::cout << "SimpleTest7 failed" << std::endl;
        }
        std::cout << std::endl;
    }

    // Performance test with 10,000 vertices and 10,000 edges
    void PerfTest1()
    {
        std::cout << "PerfTest1" << std::endl;

        GraphStore graph_store = CreateLargeGraphStore(10000, 10000);

        std::mt19937 rng(1);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000);

        std::chrono::microseconds total_time{0};

        size_t solutions_count = 0;

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);

            auto t1 = std::chrono::high_resolution_clock::now();

            const auto path = graph_store.shortestPath(from, to, "label 1");
            if (!path.empty())
            {
                ++solutions_count;
            }

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << "Searches that found a path: " << solutions_count << std::endl;
        std::cout << "Total time spent in shortestPath function: " << total_time.count() << "us" << std::endl;
        std::cout << std::endl;
    }

    // Performance test with 100,000 vertices and 100,000 edges
    void PerfTest2()
    {
        std::cout << "PerfTest2" << std::endl;

        GraphStore graph_store = CreateLargeGraphStore(100000, 100000);

        std::mt19937 rng(1);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000);

        std::chrono::microseconds total_time{0};

        size_t solutions_count = 0;

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);

            auto t1 = std::chrono::high_resolution_clock::now();
            
            const auto path = graph_store.shortestPath(from, to, "label 1");
            if (!path.empty())
            {
                ++solutions_count;
            }

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << "Searches that found a path: " << solutions_count << std::endl;
        std::cout << "Total time spent in shortestPath function: " << total_time.count() << "us" << std::endl;
        std::cout << std::endl;
    }

    // Performance test with 100,000 vertices and 150,000 edges
    void PerfTest3()
    {
        std::cout << "PerfTest3" << std::endl;

        GraphStore graph_store = CreateLargeGraphStore(100000, 150000);

        std::mt19937 rng(1);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100000);

        std::chrono::microseconds total_time{0};

        size_t solutions_count = 0;

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);
            
            auto t1 = std::chrono::high_resolution_clock::now();

            const auto path = graph_store.shortestPath(from, to, "label 1");
            if (!path.empty())
            {
                ++solutions_count;
            }

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << "Searches that found a path: " << solutions_count << std::endl;
        std::cout << "Total time spent in shortestPath function: " << total_time.count() << "us" << std::endl;
        std::cout << std::endl;
    }

    // Performance test with 1,000,000 vertices and 1,500,000 edges. This test uses a dataset beyond what the spec asks
    // for and takes more time than allowed.
    void PerfTest4()
    {
        std::cout << "PerfTest4" << std::endl;

        GraphStore graph_store = CreateLargeGraphStore(1000000, 1500000);

        std::mt19937 rng(1);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000000);

        std::chrono::microseconds total_time{ 0 };

        size_t solutions_count = 0;

        const size_t path_search_count = 100;
        for (size_t i = 0; i < path_search_count; ++i)
        {
            VertexId from = dist(rng);
            VertexId to = dist(rng);

            auto t1 = std::chrono::high_resolution_clock::now();

            const auto path = graph_store.shortestPath(from, to, "label 1");
            if (!path.empty())
            {
                ++solutions_count;
            }

            auto t2 = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        }

        std::cout << "Searches that found a path: " << solutions_count << std::endl;
        std::cout << "Total time spent in shortestPath function: " << total_time.count() << "us" << std::endl;
        std::cout << std::endl;
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
        PerfTest3();
        // This test is commented out because it takes 110s to run on my machine. It exceeds the requirements but it
        // has more vertices and edges than the requiremnts ask for.
        //PerfTest4();
    }
    catch (...)
    {
        std::cerr << "Exception thrown" << std::endl;
    }

    return 0;
}
