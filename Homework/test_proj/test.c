#include <stdio.h>
#include <stdlib.h>
#define maxsize 10
typedef int elemtype;

typedef struct edgenode
{
    struct edgenode *next;
    int adjvex;
    int weight;
} edgenode;

typedef struct vexnode
{
    elemtype data;       // 存储顶点的名称或其相关信息
    edgenode *firstedge; // 边表头指针
} vexnode;

typedef struct
{
    vexnode vexlist[maxsize]; // 顶点表
    int n, e;
} graph;

int locatevex(graph g, elemtype v)
{
    int i;
    for (i = 0; i < g.n; i++)
        if (g.vexlist[i].data == v)
            return i;
    return -1;
}

void print(graph *g)
{
    int i;
    edgenode *p;
    printf("图的邻接表表示：");
    for (i = 0; i < g->n; i++)
    {
        printf("\n%4c", g->vexlist[i].data);
        p = g->vexlist[i].firstedge;
        while (p != NULL)
        {
            printf("-->%d", p->adjvex);
            p = p->next;
        }
    }
    printf("\n");
}

void creategraph(graph *g)
{
    int k, m, n;
    elemtype v1, v2;
    edgenode *s;
    g = (graph *)malloc(sizeof(graph));
    printf("请输入图的顶点数及边数\n");
    printf("顶点数 n=");
    scanf("%d", &g->n);
    printf("边  数 e=");
    scanf("%d", &g->e);
    fflush(stdin);
    printf("请输入图的顶点信息：\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d\n", g->n);
        printf("%d\n", i);
        scanf("%d", &g->vexlist[i].data); // 构造顶点信息
        g->vexlist[i].firstedge = NULL;
    }
    printf("请输入图的边的信息：\n");
    for (k = 0; k < g->e; k++)
    {
        printf("请输入第%d条边的两个端点下标:", k + 1);
        scanf("%d%d", &v1, &v2);
        m = locatevex(*g, v1);
        n = locatevex(*g, v2);
        if (m >= 0 && n >= 0)
        {
            s = (edgenode *)malloc(sizeof(edgenode));
            s->adjvex = n;
            s->next = g->vexlist[m].firstedge;
            g->vexlist[m].firstedge = s;
        }
    }
}

int main()
{
    graph *g;
    creategraph(g);
    print(g);

    return 0;
}