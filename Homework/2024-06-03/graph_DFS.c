#include <stdio.h>
#define MAXVEX 100

typedef struct EdgeNode
{
    int adjvex;            // 邻接点域，存储该顶点对应的下标
    struct EdgeNode *next; // 链域，指向下一个邻接点
} EdgeNode;

typedef struct VertexNode
{
    int in;              // 顶点信息
    EdgeNode *firstedge; // 边表头指针
} VertexNode;

typedef struct
{
    VertexNode adjList[MAXVEX]; // 邻接表
    int n, e;                   // 图中当前的顶点数和边数
} GraphAdjList;

void DFS(GraphAdjList *G, int i, int j, int *visited)
{
    EdgeNode *p;
    visited[i] = 1;
    if (i == j)
        return;
    p = G->adjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex, j, visited);
        p = p->next;
    }
}

int existPath(GraphAdjList *G, int i, int j)
{
    int visited[MAXVEX] = {0};
    DFS(G, i, j, visited);
    if (visited[j])
        return 1;
    else
        return 0;
}