#include <stdio.h>
#define MAX_N 100
int rank[MAX_N];

//__________LIST___________
typedef struct
{
    int data[MAX_N]; // mảng bao gồm các phần tử của danh sách
    int size;            // độ dài của danh sách
} List;

void make_null_list(List *pL)
{
    pL->size = 0;
    // (*L).size=0;
}

// Thêm một phần tử mới vào cuối ds
void push_back(List *pL, int x)
{

        // pL->data[pL->size] = x;
        // pL->size++;
        pL->data[pL->size++] = x;
    
}

// Trả về phần tử ở vị trí p
int element_at(List *pL, int i)
{
    return pL->data[i-1];
}

void copy_list(List *pS1, List *pS2) {
    make_null_list(pS1);
    for (int i = 1; i <= pS2->size; i++)
        push_back(pS1, element_at(pS2, i));
}

//________________QUEUE___________________

typedef struct
{
    int data[MAX_N];
    int front, rear;
} Queue;

// khoi tao hang doi
void make_null_queue(Queue *pQ)
{
    pQ->front = 0;
    pQ->rear = -1;
}

// dua ptu vao cuoi hang doi
void enqueue(Queue *pQ, int u)
{
    pQ->rear++;
    pQ->data[pQ->rear] = u;
}

int front(Queue *pQ)
{
    return pQ->data[pQ->front];
}

void dequeue_queue(Queue *pQ)
{
    pQ->front++;
}

int empty_queue(Queue *pQ)
{
    return pQ->front > pQ->rear;
}

//________________Graph________________

typedef struct
{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v] += 1;
    // pG->A[v][u] = 1;
    pG->m++;
}

//______________________TOPO____________________________

void topo_sort(Graph *pG, List *pL)
{
    int d[MAX_N]; // luu bac vao cua dinh u

    // tính bậc vào của đỉnh u
    for (int u = 1; u <= pG->n; u++)
    {
        d[u] = 0;
        for (int x = 1; x <= pG->n; x++)
            if (pG->A[x][u] != 0) // bậc vào của u
                d[u]++;
    }

    Queue Q;
    // làm rỗng hàng đợi
    make_null_queue(&Q);

    // đưa các đỉnh có d[u] = 0 vào hàng đợi
    for (int u = 1; u <= pG->n; u++)
    {
        if (d[u] == 0)
            enqueue(&Q, u);
    }

    // làm rỗng danh sách
    make_null_list(pL);

    for(int u = 1; u< pG->n; u++)
        rank[u] = 0;
    // vòng lặp chính, lặp đến khi Q rỗng thi dừng
    while (!empty_queue(&Q))
    {
        int u = front(&Q); // lấy đỉnh đầu tiên trong Q => gọi nó là đỉnh u
        dequeue_queue(&Q);
        push_back(pL, u);  // đưa u vào cuối danh sách

        // xóa đỉnh u <=> giảm bâc vào của các đỉnh kề v của u
        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->A[u][v] != 0)
            {
                d[v]--;
                if (d[v] == 0)
                    enqueue(&Q, v);
            }
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
	    printf("%d ", element_at(&L, i));
	
	return 0;
}

