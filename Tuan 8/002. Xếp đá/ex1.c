#include <stdio.h>

#define MAX_N 100
typedef struct {
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;


void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
}


typedef struct {
    int data[MAX_N];
    int size;
} List;

void make_null_list(List *pL) {
    pL->size = 0;
}

void push_back(List *pL, int x) {
    pL->data[pL->size++] = x;
}

int element_at(List *pL, int i) {
    return pL->data[i-1];
}

void copy_list(List *pS1, List *pS2) {
    make_null_list(pS1);
    for (int i = 1; i <= pS2->size; i++)
        push_back(pS1, element_at(pS2, i));
}

typedef struct {
    int data[MAX_N];
    int front, rear;
} Queue;

void make_null_queue(Queue *pQ) {
    pQ->front = -1;
    pQ->rear  = -1;
}

void enqueue(Queue *pQ, int x) {
    pQ->rear = (pQ->rear + 1)%MAX_N;
    pQ->data[pQ->rear] = x;
    if (pQ->front == -1)
        pQ->front = 0;
}

int empty_queue(Queue *pQ) {
    return pQ->rear == -1;
}

int front(Queue *pQ) {
    return pQ->data[pQ->front];
}

void dequeue(Queue *pQ) {
    if (pQ->front == pQ->rear)
        make_null_queue(pQ);
    else
        pQ->front = (pQ->front + 1)%MAX_N;
}

void topo_sort(Graph *pG, List *pL) {
	int d[MAX_N];
	//Tính bậc vào của u
	for (int u = 1; u <= pG->n; u++) {
		d[u] = 0;
		for (int x = 1; x <= pG->n; x++)
			if (pG->A[x][u] != 0)
				d[u]++;
	}

	Queue Q;
	//Làm rỗng hàng đợi Q
	make_null_queue(&Q);
	//Đưa các đỉnh có d[u] = 0 vào hàng đợi
	for (int u = 1; u <= pG->n; u++)
		if (d[u] == 0)
			enqueue(&Q, u);
	//Làm rỗng danh sách pL
	make_null_list(pL);
	//Vòng lặp chính, lặp đến khi Q rỗng thì dừng
	while (!empty_queue(&Q)) {
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		//Xoá đỉnh u <=> giảm bậc vào của các đỉnh kề v của u
		for (int v = 1; v <= pG->n; v++)
			if (pG->A[u][v] != 0) {
				d[v]--;
				if (d[v] == 0)
					enqueue(&Q, v);
			}
	}
}



int main() {
    Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	List L;
	topo_sort(&G, &L);
	for (int i = 1; i <= L.size; i++)
	    printf("%d\n", element_at(&L, i));
	
	return 0;
}
