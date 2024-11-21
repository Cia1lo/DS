#include <stdio.h>
#include <stdlib.h>
#define   MaxVexNum  30    //最大顶点数
typedef  struct  ArcNode   //表结点定义
{  
   int  adjvex;
   struct  ArcNode  *nextarc;
}ArcNode;
typedef  struct        //头结点定义
{  
   ArcNode  *firstarc;
}VerNode;
typedef  struct 
{  
   VerNode  vertices[MaxVexNum];
   int   vernum, arcnum;
}ALGraph;

void CreatALGraph(ALGraph* G)
{
    ArcNode *newArc;

    scanf("%d %d", &G->vernum, &G->arcnum);
    
    for (size_t i = 0; i < G->vernum; i++)
    {
        G->vertices[i].firstarc = NULL;
    }
    for (size_t i = 0; i < G->arcnum; i++)
    {
        int m, n;
        scanf("%d %d", &m, &n);
        newArc = (ArcNode *)malloc(sizeof(ArcNode));
        newArc->adjvex = n;
        newArc->nextarc = G->vertices[m].firstarc;
        G->vertices[m].firstarc = newArc;

        newArc = (ArcNode *)malloc(sizeof(ArcNode));
        newArc->adjvex = m;
        newArc->nextarc = G->vertices[n].firstarc;
        G->vertices[n].firstarc = newArc;
    }
}

void DFS(ALGraph* G, int start, bool visited[])
{
    visited[start] = true;
    printf("%d ", start);
    ArcNode *p = G->vertices[start].firstarc; 
    
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFS(G, p->adjvex, visited);
        }
        p = p->nextarc;
    }
}


int main()
{
    ALGraph G;
    CreatALGraph(&G);
    bool visited[MaxVexNum] = {false};
    for (int i = 0; i < G.vernum; i++) {
        if (!visited[i]) {
            DFS(&G, i, visited);  // 从未访问的顶点开始新的 DFS
        }
    }
    return 0;
}