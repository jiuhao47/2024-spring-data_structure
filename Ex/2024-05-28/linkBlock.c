#include <stdio.h>
void DFS(int *graph, int node_num, int point_valid[], int i);
int main()
{
    int node_num;
    scanf("%d", &node_num);
    int graph[node_num][node_num];
    for (int i = 0; i < node_num; i++)
    {
        for (int j = 0; j < node_num; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    int linkBlock_num = 0;
    int point_valid[node_num];
    for (int i = 0; i < node_num; i++)
    {
        point_valid[i] = 0;
    }
    for (int i = 0; i < node_num; i++)
    {
        if (point_valid[i] == 0)
        {
            linkBlock_num++;
            DFS(graph[0], node_num, point_valid, i);
        }
    }
    // 求联通分量数量

    printf("%d\n", linkBlock_num - 1);
}

void DFS(int *graph, int node_num, int point_valid[], int i)
{
    point_valid[i] = 1;
    for (int j = 0; j < node_num; j++)
    {
        if (graph[i * node_num + j] == 1 && point_valid[j] == 0)
        {
            DFS(graph, node_num, point_valid, j);
        }
    }
}