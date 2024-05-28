#include <stdio.h>
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
    int dist[node_num][node_num];
    // 使用Floyd算法求解最短路径
    for (int i = 0; i < node_num; i++)
    {
        for (int j = 0; j < node_num; j++)
        {
            dist[i][j] = graph[i][j];
            if (graph[i][j] == -1)
            {
                dist[i][j] = 999999;
            }
        }
    }
    for (int k = 0; k < node_num; k++)
    {
        for (int i = 0; i < node_num; i++)
        {
            for (int j = 0; j < node_num; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    for (int i = 0; i < node_num; i++)
    {
        for (int j = 0; j < node_num; j++)
        {
            if (dist[i][j] == 999999)
            {
                printf("-1 ");
            }
            else
            {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}