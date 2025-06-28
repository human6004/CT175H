#include <stdio.h>
#define max 100

int mark[max];
int parent[max];
typedef struct{
    int n,m;
    int A[max][max];
}Graph;
typedef struct{
    int u,p;
}ElementType;
typedef struct{
    ElementType data[max];
    int front,rear;
}Queue;

//khoi tao hang doi
void make_null_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

//dua ptu vao cuoi
void enqueue (Queue *pQ, ElementType u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
}

ElementType front (Queue *pQ){
    return pQ->data[pQ->front];
}

void dequeue (Queue *pQ){
    pQ->front++;
}

int empty (Queue *pQ){
    return pQ->front > pQ->rear;
}

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG-> m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}
int adjacent(Graph *pG, int u, int v)
{
    return pG->A[u][v] > 0;
}

void topo_sort(Graph *pG, ){
    
}