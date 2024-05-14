#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge
{
    int src, dest, weight;
} Edge;
typedef struct Graph
{
    int Type;
    int V;      // 顶点数
    int E;      // 边数
    Edge *edge; // 边集
} Graph;
bool graph_build(Graph *graph, int V, int E, int Type);
bool graph_build(Graph *graph, int V, int E, int Type)
{
    graph->Type = Type;
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge *)malloc(graph->E * sizeof(Edge));
    if (graph->edge)
    {
        return true;
    }
    else
    {
        return false;
        // malloc failed
    }
}

int main()
{
    Graph graph;
    int V, E;
    int Type;
    printf("Input the type of graph (0:non-vec;1:vec): ");
    scanf("%d", &Type); // 0：无向图，1：有向图
    while ((Type != 1) && (Type != 0))
    {
        printf("Invalid type! Please input again: ");
        scanf("%d", &Type);
    }
    printf("Input the number of points (>=1): ");
    scanf("%d", &V);
    while (V <= 0)
    {
        printf("Invalid point number! Please input again: ");
        scanf("%d", &V);
    }
    printf("Input the number of edges(>=0): ");
    scanf("%d", &E);
    while ((E < 0) || (E > ((Type == 1) ? (V * (V - 1)) : (V * (V - 1) / 2))))
    {
        if (V == 1 && E == 1)
        {
            break;
        }
        printf("Invalid edge number! Please input again: ");
        scanf("%d", &E);
    }

    if (!graph_build(&graph, V, E, Type))
    {
        printf("Exception: Malloc Failed!\n");
        exit(-1);
    }
    printf("Input Edges:\nPs: src,dest: 0->%d\n", graph.E - 1);
    for (int i = 0; i < graph.E; i++)
    {
        printf("Edge %d :(src dest weight): ", i);
        scanf("%d %d %d", &graph.edge[i].src, &graph.edge[i].dest, &graph.edge[i].weight);
    }
    printf("Graph show:\n");
    for (int i = 0; i < graph.E; i++)
    {
        printf("Edge %d : %d-----%d -> %d\n", i, graph.edge[i].src, graph.edge[i].dest, graph.edge[i].weight);
    }
}