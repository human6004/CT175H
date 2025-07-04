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

//kiểm tra tính liên thông
int connected(Graph *pG){
    for(int u = 1; u < pG->n; u++)
    //khởi tạo tất cả đỉnh chưa duyệt
        mark[u] = 0;
    //2. duyệt đồ thị từ đỉnh bất kì
    BFS(pG,1);
    //3. kiểm tra xem có đỉnh nào chưa được duyệt không
    for(int u=1; u < pG->n; u++)
        if(mark[u] == 0)
            return 0;
    return 1;
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
        if (mark[i] == 0) {
            BFS(&G, i);

        }
    }

    if(connected(&G)==1)
        printf("CONNECTED");
    else
        printf("DISCONNECTED");
}
