#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVexNum 30

// 表结点定义
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

// 头结点定义
typedef struct {
    ArcNode *firstarc;
} VerNode;

// 邻接表图结构定义
typedef struct {
    VerNode vertices[MaxVexNum];
    int vernum, arcnum;
} ALGraph;

// 队列定义，用于BFS
typedef struct {
    int data[MaxVexNum];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *q) {
    q->front = q->rear = 0;
}

// 判断队列是否为空
bool IsQueueEmpty(Queue *q) {
    return q->front == q->rear;
}

// 入队
void EnQueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

// 出队
int DeQueue(Queue *q) {
    return q->data[q->front++];
}

// 创建无向图邻接表
void CreateALGraph(ALGraph *G) {
    int i, j, k;
    ArcNode *newArc;

    scanf("%d %d", &G->vernum, &G->arcnum);

    // 初始化顶点的边链表为空
    for (i = 0; i < G->vernum; i++) {
        G->vertices[i].firstarc = NULL;
    }

    // 读入边信息并创建邻接表
    for (k = 0; k < G->arcnum; k++) {
        scanf("%d %d", &i, &j);

        // 头插法插入边 (i, j)
        newArc = (ArcNode *)malloc(sizeof(ArcNode));
        newArc->adjvex = j;
        newArc->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = newArc;

        // 头插法插入边 (j, i)，因为是无向图
        newArc = (ArcNode *)malloc(sizeof(ArcNode));
        newArc->adjvex = i;
        newArc->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = newArc;
    }
}

// 广度优先遍历（BFS）并计算连通分量和边数
void BFS(ALGraph *G, int start, bool visited[], int *edgeCount) {
    Queue q;
    InitQueue(&q);
    EnQueue(&q, start);
    visited[start] = true;

    while (!IsQueueEmpty(&q)) {
        int v = DeQueue(&q);
        printf("%d ", v);

        ArcNode *p = G->vertices[v].firstarc;
        while (p) {
            (*edgeCount)++;  // 每次访问一条边
            if (!visited[p->adjvex]) {
                EnQueue(&q, p->adjvex);
                visited[p->adjvex] = true;
            }
            p = p->nextarc;
        }
    }
}

int main() {
    ALGraph G;
    CreateALGraph(&G);

    bool visited[MaxVexNum] = {false};
    int componentCount = 0;
    int edgeCount = 0;

    // 广度优先遍历所有顶点
    for (int i = 0; i < G.vernum; i++) {
        if (!visited[i]) {
            componentCount++;
            BFS(&G, i, visited, &edgeCount);
        }
    }
    printf("\n");

    // 边数除以2（无向图每条边在邻接表中存了两次）
    printf("%d\n", componentCount);
    printf("%d\n", edgeCount / 2);

    return 0;
}
