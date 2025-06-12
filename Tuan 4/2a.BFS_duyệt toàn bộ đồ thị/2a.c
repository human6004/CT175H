#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
typedef struct{
    int n,m;
    int A[max][max];
}Graph;

typedef struct{
    ElementType data[max];
    int front,rear;
}Queue;

//khoi tao hang doi
void init_queue (Queue *pQ){
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

void BFS(Graph *pG, int s){
    Queue Q;
    init_queue (&Q);
    enqueue (&Q,s);
    while (!empty(&Q)){
        int u = front (&Q);
        dequeue(&Q);
        if (mark[u] != 0){
            continue;
        }
        printf ("%d\n", u);
        mark[u] = 1;
        //duyệt các cạnh kề của uu
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                enqueue (&Q,v);
            }
        }
    }
}

int main (){
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
	
    for (int e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (int i = 1; i <= G.n; i++)
    mark[i] = 0;

    for (int  u = 1; u <= G.n; u++)
    {
        if(mark[u]==0)
            BFS(&G,u);
    }
    
    
    return 0;
}

// 6 6
// 1 2
// 1 3
// 2 4
// 3 5
// 4 6
// 5 6

// 1
// 2
// 3
// 4
// 5