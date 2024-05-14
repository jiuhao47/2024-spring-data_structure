#include <stdio.h>
#include <stdlib.h>

// 定义边的结构体
typedef struct Edge
{
    int src, dest, weight;
} Edge;

// 定义图的结构体
typedef struct Graph
{
    int V, E;
    Edge *edge;
} Graph;

// 创建图
Graph *createGraph(int V, int E)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge *)malloc(graph->E * sizeof(Edge));
    return graph;
}

// 查找集合的代表元素
int find(int parent[], int i)
{
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// 合并两个集合
void Union(int parent[], int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// 卡鲁斯卡尔算法
void KruskalMST(Graph *graph)
{
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    // 按照边的权重排序
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    int *parent = (int *)malloc(V * sizeof(int));

    memset(parent, -1, sizeof(int) * V);

    while (e < V - 1)
    {
        Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    return;
}