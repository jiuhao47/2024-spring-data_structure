#include <stdio.h>
#include <stdlib.h>

#define int_max 0x7fffffff
#define maxsize 100
#define queuesize 100  

typedef char elemtype;

typedef struct graph{
    elemtype vexs[maxsize];//顶点表
    int matrix[maxsize][maxsize];//邻接矩阵
    int vexnum;
    int arcnum;//边数，顶点数
}graph;

//在图中查找顶点v,存在返回其在顶点数组中的下标，不存在返回-1
int locate(graph *g,elemtype v){
    int i;
    for(i=0;i<g->vexnum;i++){
         if(g->vexs[i]==v)
            return i;
    }     
    return -1;
}

 //打印信息
void print(graph *g){
    int i,j;
    printf("图的邻接矩阵表示：\n");
    for(i=0;i<g->vexnum;i++){
        for(j=0;j<g->vexnum;j++){
            printf("%11d",g->matrix[i][j]);
        }
        printf("\n");
    }
}
//创建有向图的邻接矩阵
void creategraph(graph *g){
    int i,j,k;
    elemtype v1,v2;
    int weight;
    printf("请输入顶点数和边数：\n");
    printf("顶点数 ");scanf("%d",&g->vexnum);
    printf("边  数 ");scanf("%d",&g->arcnum);
    printf("请输入图的顶点信息：\n");
    getchar();
    for(i=0;i<=g->vexnum;i++)
    scanf("%c",&g->vexs[i]);
    for(i=0;i<g->vexnum;i++)
        for(j=0;j<g->vexnum;j++)
            g->matrix[i][j]=int_max;//初始化邻接矩阵
    printf("请输入图的边的信息：\n");
    for(k=0;k<g->arcnum;k++)
    {
        printf("请输入第%d条边的两个端点:",k+1);
        scanf("%c%c",&v1,&v2);
        printf("请输入边的权值:");
        scanf("%d",&weight);
        fflush(stdin);
        i=locate(g,v1);
        j=locate(g,v2);
        if(i>=0&&j>=0){
        g->matrix[i][j]=weight;
        }
    }
}

void Dijkstra(graph *g,elemtype e){
    int i,j,k,v;
    int p[maxsize][maxsize];
    int dist[maxsize];
    int flag[maxsize];
    int prev[maxsize];
    v=locate(g,e);
    for(i=0;i<g->vexnum;i++){
        flag[i]=0;
        prev[i]=-1;
        dist[i]=g->matrix[v][i];

    }    
    flag[v] = 1;
    dist[v] = 0;

    for (i=1;i<g->vexnum;i++){
        int min = int_max;
        for(j=0;j<g->vexnum;j++){
            if (flag[j]==0 && dist[j]<min){
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;

        for (j=0;j<g->vexnum;j++){
            int tmp;
            if(g->matrix[k][j]==int_max)
                tmp = int_max;
            else
                tmp = min + g->matrix[k][j];
            if(flag[j]==0 && tmp<dist[j]){
                dist[j] = tmp;
                prev[j] = k;
            }    
        }   /* code */
    }
    for(i=0;i<g->vexnum;i++){
        printf("%c-",g->vexs[v]);
        int front = i;
        char stack[maxsize];
        int top = -1;
        while(prev[front]!=-1){
            front=prev[front];
            top++;
            stack[top]=g->vexs[front];    
        }
        while(top!=-1){
            printf("%c-",stack[top]);
            top--;
        }
        
        printf("%c  %d\n",g->vexs[i],dist[i]);   
    }
}

void Floyd(graph *g) {
    int i,j,k;
    int tmp;
    int p[maxsize][maxsize];
    for (i=0; i<g->vexnum;i++) {
        for (j=0; j<g->vexnum;j++) {
            p[i][j]=-1;
        }    
    }  
    for (k=0;k<g->vexnum;k++) {
        for (i=0; i<g->vexnum;i++) {
            for (j=0; j<g->vexnum;j++) {
                if(g->matrix[i][k]==int_max || g->matrix[k][j]==int_max)
                    tmp = int_max;
                else
                    tmp = g->matrix[i][k] + g->matrix[k][j];
                if(tmp < g->matrix[i][j]){
                    g->matrix[i][j] = tmp;
                    p[i][j] = k;
                }
            }
        }
    }

    for(i=0;i<g->vexnum;i++){
        g->matrix[i][i] = 0;
    }
    
    for (i=0;i<g->vexnum;i++){
        for (j=0; j<g->vexnum;j++){
            printf("%c-",g->vexs[i]);
            tmp = p[i][j];
            while(tmp != j && tmp != -1){
                printf("%c-",g->vexs[tmp]);
                tmp = p[tmp][j];
            }
            printf("%c  %d\n",g->vexs[j],g->matrix[i][j]); 
        }
    }
}


int main(){
    graph *g;
    elemtype e;
    g=(graph *)malloc(sizeof(graph));
    creategraph(g);
    print(g);
    printf("请输入想求的最短路径起点：\n");
    scanf("%c",&e);
    printf("%c到各点的最短路径及长度为(Dijkstra):\n",e);
    Dijkstra(g,e);
    printf("任意两点间的最短路径及长度为(Floyd):\n");
    Floyd(g);
}