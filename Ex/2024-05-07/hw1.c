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
    int V;      // 顶点数
    int E;      // 边数
    Edge *edge; // 边集
} Graph;
bool graph_build(Graph *graph, int V, int E);
int compareEdges(const void *a, const void *b);
void InPoint(int *point_in, int *point_out, int index);
bool elementIn(int *point_in, int *point_out, Graph *graph, int index);
Edge findMin(int *point_in, int *point_out, Graph *graph);
bool isFull(int *point_in, int size);
bool PrimMST(Graph *graph);
int find(int *parent, int i);
void Union(int *parent, int x, int y);
void KruskalMST(Graph *graph);
bool graph_build(Graph *graph, int V, int E)
{
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
int compareEdges(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight - e2->weight;
}
void InPoint(int *point_in, int *point_out, int index)
{
    point_in[index] = 1;
    point_out[index] = 0;
}
bool elementIn(int *point_in, int *point_out, Graph *graph, int index)
{
    // 对point_in作遍历，权值最小的索引为index的边是否满足由point_in到point_out的条件
    for (int i = 0; i < graph->V; i++)
    {
        if ((point_in[graph->edge[index].src] == 1) && (point_out[graph->edge[index].dest] == 1))
        {
            InPoint(point_in, point_out, graph->edge[index].dest); // 更新剩余节点
            return true;
        }
        if ((point_in[graph->edge[index].dest] == 1) && (point_out[graph->edge[index].src] == 1))
        {
            InPoint(point_in, point_out, graph->edge[index].src); // 更新剩余节点
            return true;
        }
    }
    return false;
}
Edge findMin(int *point_in, int *point_out, Graph *graph)
{
    Edge temp;
    for (int i = 0; i < graph->E; i++)
    {
        // 对每条边作遍历，找到由point_in到point_out中最小权的边
        if (elementIn(point_in, point_out, graph, i))
        {
            temp.dest = graph->edge[i].dest;
            temp.src = graph->edge[i].src;
            temp.weight = graph->edge[i].weight;
            graph->edge[i].weight = INT_MAX; // 更新已经进入的边权值
            return temp;
        }
    }
}
bool isFull(int *point_in, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (point_in[i] == 0)
        {
            return false;
        }
    }
    return true;
}
bool PrimMST(Graph *graph)
{
    Edge MST[graph->V - 1];
    int point_in[graph->V];
    int point_out[graph->V];
    for (int i = 0; i < graph->V; i++)
    {
        point_in[i] = 0;
        point_out[i] = 1;
    }
    InPoint(point_in, point_out, 0);
    int index = 0;
    while (!isFull(point_in, graph->V))
    {
        qsort(graph->edge, graph->E, sizeof(Edge), compareEdges);
        MST[index] = findMin(point_in, point_out, graph);
        index = index + 1;
    }
    printf("Prim Tree show:\n");
    for (int i = 0; i < graph->V - 1; i++)
    {
        printf("Edge %d : %d-----%d -> %d\n", i, MST[i].src, MST[i].dest, MST[i].weight);
    }
    return true;
}
int find(int *parent, int i)
{
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// 合并两个集合
void Union(int *parent, int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// 卡鲁斯卡尔算法
void KruskalMST(Graph *graph)
{
    Edge MST[graph->V - 1];
    int e = 0;
    int i = 0;
    // 按照边的权重排序
    qsort(graph->edge, graph->E, sizeof(Edge), compareEdges);
    int *parent = (int *)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++)
    {
        parent[i] = -1;
    }
    while (e < graph->V - 1)
    {
        Edge next_edge = graph->edge[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest); // already root
        if (x != y)
        {
            MST[e++] = next_edge;
            Union(parent, x, y);
        }
    }
    printf("Kruskal Tree Show\n");
    for (i = 0; i < e; ++i)
    {
        printf("Edge %d : %d-----%d -> %d\n", i, MST[i].src, MST[i].dest, MST[i].weight);
    }
    return;
}
int main()
{
    Graph graph;
    int V, E;
    printf("Input the number of points (>=1): ");
    scanf("%d", &V);
    while (V <= 0)
    {
        printf("Invalid point number! Please input again: ");
        scanf("%d", &V);
    }
    printf("Input the number of edges(>=0): ");
    scanf("%d", &E);
    while ((E < 0) || (E > (V * (V - 1) / 2)))
    {
        if (V == 1 && E == 1)
        {
            break;
        }
        printf("Invalid edge number! Please input again: ");
        scanf("%d", &E);
    }

    if (!graph_build(&graph, V, E))
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
    // 输入需要进一步规范非法输入；
    printf("Graph show:\n");
    for (int i = 0; i < graph.E; i++)
    {
        printf("Edge %d : %d-----%d -> %d\n", i, graph.edge[i].src, graph.edge[i].dest, graph.edge[i].weight);
    }
    KruskalMST(&graph);
    PrimMST(&graph);
    return 0;
}