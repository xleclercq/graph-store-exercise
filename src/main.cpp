#include "graphstore.h"

int main(int argc, char* argv[])
{
    GraphStore graph_store;

    VertexId v_id_1 = graph_store.createVertex();
    VertexId v_id_2 = graph_store.createVertex();

    graph_store.createEdge(v_id_1, v_id_2);

    return 0;
}
