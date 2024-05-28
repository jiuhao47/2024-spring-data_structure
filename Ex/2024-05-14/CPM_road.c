#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
typedef struct Edge
{
    int src, dest, weight, valid;
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
void in_degree_cal(Graph *graph, int *in_degree);
bool Topological_Sort(Graph *graph, int *point_output);
int zero_in_degree_find(Graph *graph, int *in_degree, int *point_valid);
void CPM_road(Graph *graph, int *point_output_sort);
bool Topological_Sort(Graph *graph, int *point_output)
{
    int point_valid[graph->V]; // 点是否被删除
    // int point_output[graph->V];
    int output_index = 0;
    for (int i = 0; i < graph->V; i++)
    {
        point_valid[i] = 1;
        point_output[graph->V] = -1;
    }
    int in_degree[graph->V];
    in_degree_cal(graph, in_degree);
    int index = -1;
    while ((index = zero_in_degree_find(graph, in_degree, point_valid)) > -1)
    {
        // printf("Delete %d\n", index);
        point_valid[index] = 0;
        point_output[output_index] = index;
        output_index++;
        for (int i = 0; i < graph->E; i++)
        {
            if (graph->edge[i].src == index)
            {
                graph->edge[i].valid = 0;
            }
        }
        in_degree_cal(graph, in_degree);
    }
    for (int i = 0; i < graph->E; i++)
    {
        graph->edge[i].valid = 1;
    }
    if (index == -1)
    {
        return true;
    }
    else
    {
        printf("Ring exists!\n");
        return false;
    }
}
// in_degree为每个顶点的入度
void in_degree_cal(Graph *graph, int *in_degree)
{
    for (int i = 0; i < graph->V; i++)
    {
        in_degree[i] = 0;
    }
    for (int i = 0; i < graph->E; i++)
    {
        if (graph->edge[i].valid > 0)
        {
            in_degree[graph->edge[i].dest]++;
        }
    }
}

int zero_in_degree_find(Graph *graph, int *in_degree, int *point_valid)
{
    int temp = -1;
    for (int i = 0; i < graph->V; i++)
    {
        if (point_valid[i] == 1)
        {
            temp = temp - 1;
        }
        if (in_degree[i] == 0 && point_valid[i] == 1)
        {
            return i;
        }
    }
    return temp;
    // temp:-1: 点集已空 else:未空
}

void CPM_road(Graph *graph, int *point_output_sort)
{
    int ve[graph->V];
    int vl[graph->V];
    int e[graph->E];
    int l[graph->E];
    int l_sub_e[graph->E];
    for (int i = 0; i < graph->V; i++)
    {
        ve[i] = 0;
        vl[i] = INT_MAX;
    }
    for (int i = 0; i < graph->E; i++)
    {
        e[i] = l[i] = 0;
    }
    // ve为正常点顺序
    ve[0] = 0;
    // i拓扑序
    for (int i = 1; i < graph->V; i++)
    {
        for (int j = 0; j < graph->E; j++)
        {
            if (graph->edge[j].dest == point_output_sort[i])
            {
                ve[point_output_sort[i]] = (ve[point_output_sort[i]] > ve[graph->edge[j].src] + graph->edge[j].weight) ? ve[point_output_sort[i]] : ve[graph->edge[j].src] + graph->edge[j].weight;
            }
        }
    }
    vl[graph->V - 1] = ve[graph->V - 1];
    // i拓扑序
    for (int i = graph->V - 1; i > 0; i--)
    {
        for (int j = 0; j < graph->E; j++)
        {
            if (graph->edge[j].dest == point_output_sort[i])
            {
                vl[graph->edge[j].src] = (vl[graph->edge[j].src] < vl[point_output_sort[i]] - graph->edge[j].weight) ? vl[graph->edge[j].src] : vl[point_output_sort[i]] - graph->edge[j].weight;
            }
        }
    }
    for (int i = 0; i < graph->V; i++)
    {
        // printf("ve[%d]=%d vl[%d]=%d\n", i, ve[i], i, vl[i]);
    }
    for (int i = 0; i < graph->E; i++)
    {
        e[i] = ve[graph->edge[i].src];
        l[i] = vl[graph->edge[i].dest] - graph->edge[i].weight;
        l_sub_e[i] = l[i] - e[i];
        // printf("e[%d]=%d,l[%d]=%d\n", i, e[i], i, l[i]);
    }
    for (int i = 0; i < graph->E; i++)
    {
        if (l_sub_e[i] == 0)
        {
            printf("Edge %d : %d-----%d -> %d\n", i, graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
        }
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
    printf("Input Edges:\nPs: src,dest: 0->%d\n", graph.V - 1);
    for (int i = 0; i < graph.E; i++)
    {
        printf("Edge %d :(src dest weight): ", i);
        scanf("%d %d %d", &graph.edge[i].src, &graph.edge[i].dest, &graph.edge[i].weight);
        graph.edge[i].valid = 1;
    }
    printf("Graph show:\n");
    for (int i = 0; i < graph.E; i++)
    {
        printf("Edge %d : %d-----%d -> %d\n", i, graph.edge[i].src, graph.edge[i].dest, graph.edge[i].weight);
    }
    int point_output_sort[graph.V];

    if (Topological_Sort(&graph, point_output_sort))
    {
        printf("TopologicalSort output:");
        for (int i = 0; i < graph.V; i++)
        {
            printf("%d ", point_output_sort[i]);
        }
        printf("\n");
        CPM_road(&graph, point_output_sort);
    }
}