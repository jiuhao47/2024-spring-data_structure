#include <stdio.h>
#include <stdlib.h>

#define int_max 0x7fffffff
#define maxsize 10
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
        printf("请输入第%d条边的两个端点及权值:",k+1);
        scanf("%c%c%d",&v1,&v2,&weight);
        fflush(stdin);//清空输入缓冲区
        i=locate(g,v1);
        j=locate(g,v2);
        if(i>=0&&j>=0){
        g->matrix[i][j]=weight;
        g->matrix[j][i]=weight;
        }
    }
}

void prim(graph *g, elemtype e){
    struct {
        elemtype adjvex;
        int lowcost;
    }closedge[maxsize];
    
    int i; 
    int k = locate(g,e);
    for (i=0; i<g->vexnum; i++){
        if (i!=k){
            closedge[i].adjvex=e;
            closedge[i].lowcost=g->matrix[k][i];
        } 
    }
    closedge[k].lowcost=0;
    closedge[k].adjvex=e;
    for (i=1; i<g->vexnum; i++){
        int min = int_max;
        for (int j=0; j<g->vexnum; j++)
            if(closedge[j].lowcost < min && closedge[j].lowcost != 0){
                min = closedge[j].lowcost;
                k = j;
            }
        printf("%c-%c %d\n",closedge[k].adjvex,g->vexs[k],closedge[k].lowcost);
        closedge[k].lowcost=0;
        for(int t=0;t<g->vexnum;t++){
            if(g->matrix[k][t]<closedge[t].lowcost){
                closedge[t].adjvex=g->vexs[k];
                closedge[t].lowcost=g->matrix[k][t];
            }          
        }
    }
}

int find(int parent[maxsize],int infront){
    while (parent[infront]!=-1){
        infront = parent[infront];      
    }
    return infront;
}

void Kruskal(graph *g){
    int i,j,k,w,m,n;
    int startid,endid;
    int parent[maxsize];
    for(i=0;i<g->vexnum;i++){
        parent[i]=-1;
    }
    char start,end;
    for (k=0; k<g->arcnum; k++){
        int min = int_max;
        for (i=0; i<g->vexnum; i++){
            for (j=0; j<g->vexnum; j++){
                if(g->matrix[i][j] < min){
                    min = g->matrix[i][j];
                    startid = i;
                    endid = j;
                    start = g->vexs[i];
                    end = g->vexs[j]; 
                }
            }
        }
        g->matrix[startid][endid]=INT_MAX;
        g->matrix[endid][startid]=INT_MAX;
        m = find(parent,startid);
        n = find(parent,endid);

        if(m!=n){
            parent[n] = m;
            printf("%c-%c %d\n",start,end,min);
        }
    }
}


int main(){
    graph *g;
    elemtype e;
    g=(graph *)malloc(sizeof(graph));
    creategraph(g);
    print(g);
    printf("请输入出发顶点：");
    scanf("%c",&e);
    printf("最小生成树的边与对应长度(Prim):\n");
    prim(g,e);
    printf("最小生成树的边与对应长度(Kruskal):\n");
    Kruskal(g);
    return 0;
}
