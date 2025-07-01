#include <stdio.h>
#define MAX_N 100

//__________LIST___________
typedef struct
{
    int data[MAX_N]; // mảng bao gồm các phần tử của danh sách
    int size;        // độ dài của danh sách
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
    return pL->data[i - 1];
}

void copy_list(List *pS1, List *pS2)
{
    make_null_list(pS1);
    for (int i = 1; i <= pS2->size; i++)
        push_back(pS1, element_at(pS2, i));
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

//______________________xếp hạng____________________________
int r[MAX_N]; // hàm xếp hạng
void rank(Graph *pG)
{
    int d[MAX_N]; // luu bac vao cua dinh u

    // tính bậc vào của đỉnh d[u]
    for (int u = 1; u <= pG->n; u++)
    {
        d[u] = 0;
        for (int x = 1; x <= pG->n; x++)
            if (pG->A[x][u] != 0) // bậc vào của u
                d[u]++;
    }

    // Sử dụng 2 danh sách S1, S2
    List S1, S2;

    // Tìm gốc, đưa vào S1
    make_null_list(&S1); // khởi tạo rỗng cho s1
    for (int u = 1; u < pG->n; u++)
        if (d[u] == 0)
            push_back(&S1, u);

    int k = 1; // hạng tính từ 0. Tùy theo bài toán có thẻ k = 1

    // vòng lặp chính, lặp đến khi S1 rỗng thi dừng
    while (S1.size > 0)
    {
        make_null_list(&S2); // khởi tạo rỗng cho s2
        for (int i = 1; i <= S1.size; i++)
        {
            int u = element_at(&S1, i); // lấy các gốc u trong S1 ra
            r[u] = k;                   // xếp hạng cho u

            // xóa đỉnh u <=> giảm bâc vào của các đỉnh kề v của u
            for (int v = 1; v <= pG->n; v++)
                if (pG->A[u][v] != 0)
                {
                    d[v]--;
                    if (d[v] == 0)
                        push_back(&S2, v);
                }
        }
        copy_list(&S1, &S2); // copy s2 vào s1
        k++;                 // tăng hạng kế tiếp cho các gốc mới
    }
}

int main()
{
    Graph G;
    int n, m, u, v, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, v, u);
    }

    rank(&G);
	int sum = 0;
	for (int u = 1; u <= n; u++) {
	    printf("%d\n", r[u]);
	    sum += r[u];
	}
    printf("%d\n", sum);
    return 0;
}
