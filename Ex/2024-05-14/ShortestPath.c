#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
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
void printSolution_d(int dist[], int vertices);
void dijkstra(Graph *graph, int src);
void printSolution_f(int *dist, int vertices);
void floydWarshall(Graph *graph);
bool graph_build(Graph *graph, int V, int E, int Type);
int minDistance(int dist[], bool sptSet[], int vertices);
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
    dijkstra(&graph, 0);
    floydWarshall(&graph);
}
int minDistance(int dist[], bool sptSet[], int vertices)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution_d(int dist[], int vertices)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < vertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(Graph *graph, int src)
{
    int vertices = graph->V;
    int dist[vertices];

    bool sptSet[vertices];

    for (int i = 0; i < vertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; count++)
    {
        int u = minDistance(dist, sptSet, vertices);

        sptSet[u] = true;

        for (int v = 0; v < vertices; v++)
        {
            for (int e = 0; e < graph->E; e++)
            {
                if (graph->edge[e].src == u && graph->edge[e].dest == v && dist[u] != INT_MAX && dist[u] + graph->edge[e].weight < dist[v])
                    dist[v] = dist[u] + graph->edge[e].weight;
            }
        }
    }

    printSolution_d(dist, vertices);
}

void printSolution_f(int *dist, int vertices)
{
    printf("The following matrix shows the shortest distances between every pair of vertices \n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (dist[i * vertices + j] == 9999)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i * vertices + j]);
        }
        printf("\n");
    }
}

void floydWarshall(Graph *graph)
{
    int vertices = graph->V;
    int dist[vertices][vertices];

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = 9999;
    for (int i = 0; i < vertices; i++)
    {
        dist[i][i] = 0;
    }
    for (int e = 0; e < graph->E; e++)
    {
        dist[graph->edge[e].src][graph->edge[e].dest] = graph->edge[e].weight;
    }

    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolution_f(dist[0], vertices);
}

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