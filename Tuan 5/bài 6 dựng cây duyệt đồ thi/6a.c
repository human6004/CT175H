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


void BFS(Graph *pG, int s){
    Queue Q;
    make_null_queue (&Q);
    
    ElementType pair;
    pair.u = s;
    pair.p = -1;
    enqueue(&Q,pair);
    while (!empty(&Q)){
        ElementType pair = front(&Q);
        int u = pair.u;
        int p = pair.p;
        dequeue(&Q);

        if (mark[u] != 0){
            continue;
        }
        // printf ("%d\n", u);
        mark[u] = 1;
        parent[u]= p;
        //duyệt các cạnh kề của uu
        for (int v = 1; v <= pG->n; v++){
            if (adjacent(pG,u,v)){
                ElementType pair;
                pair.u =v;
                pair.p =u;
                enqueue (&Q,pair);
            }
        }
    }
}

int main (){
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);

    init_graph(&G, n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for (int i = 1; i <= n; i++) {
        mark[i] = 0;
        parent[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        if (mark[i] == 0) {
            BFS(&G, i);

        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, parent[i]);
    }

}
/*
2 1
1 4
2 4

1 -1
2 1
3 -1
4 1
*/

/*
	
4 2
1 2
3 4

1 -1
2 1
3 -1
4 3
*/

/*
4 2
1 4
2 3
1 -1
2 -1
3 2
4 1
*/