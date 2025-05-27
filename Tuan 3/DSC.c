#include <stdio.h>
// Định nghĩa hằng MAX_M: số cung tối đa đồ thị có thể chứa
#define MAX_M 500
// Định nghĩa cấu trúc dữ liệu Edge biểu diễn 1 cung (u, v)
typedef struct
{
    // Mỗi cung lưu đỉnh đầu u, đỉnh cuối v
    int u, v;
} Edge;
// Định nghĩa cấu trúc dữ liệu Graph biểu diễn 1 đồ thị
typedef struct
{
    // n: đỉnh, m: cung
    int n, m;
    // Mảng edges lưu các cung của đồ thị
    Edge edges[MAX_M];
} Graph;

// khởi tạo đồ thị G có n đỉnh
void init_graph(Graph *pG, int n)
{
    pG->n = n; // n đỉnh
    pG->m = 0; // 0 cung/cạnhcạnh
}

// Thêm cung u và vào đồ thị do pG trỏ đến
// add_edge ơ bản
void add_edge(Graph *pG, int u, int v)
{
    // đưa cung (u,v) vào edges
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

// add_edge nâng cao 2
void add_edgeX(Graph *pG, int u, int v)
{
    if (u < 1 || v > pG->n)
        return;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

// add_edge nâng cao so 3
void add_edge(Graph *pG, int u, int v)
{
    // Duyệt qua các cung đã có để kiểm tra xem (u, v) đã tồn tại hay chưa
    for (int i = 0; i < pG->m; i++)
    {
        if ((pG->edges[i].u == u && pG->edges[i].v == v) || (pG->edges[i].u == v && pG->edges[i].v == u))
            return; // Nếu cung đã tồn tại, không thêm nữa
    }

    // Nếu chưa tồn tại, thêm cung mới vào danh sách
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

// Kiểm tra đỉnh u có kề với đỉnh v trong đồ thị vô hướng
int adjacent(Graph *pG, int u, int v)
{
    int e;
    // Duyệt qua từng cung 0, 1, 2, ..., m - 1
    for (e = 0; e < pG->m; e++)
        if ((pG->edges[e].u == u && pG->edges[e].v == v) ||
            (pG->edges[e].u == v && pG->edges[e].v == u))
            return 1;

    // Không có cung nào có dạng (u, v) hoặc (v, u)
    return 0;
}

// Kiểm tra đỉnh u có kề với đỉnh v trong đồ thị có hướng
int adjacentXX(Graph *pG, int u, int v)
{
    int e;
    // Duyệt qua từng cung 0, 1, 2, ..., m - 1
    for (e = 0; e < pG->m; e++)
        if (pG->edges[e].u == u && pG->edges[e].v == v)
            return 1;

    // Không có cung nào có dạng (u, v) hoặc (v, u)
    return 0;
}

// Đếm bậc của đỉnh u của đồ thị bất kỳ
int degree(Graph *pG, int u)
{
    int e, deg_u = 0;
    // Duyệt qua từng cung 0, 1, 2, ..., m - 1
    for (e = 0; e < pG->m; e++)
    {
        // Nếu cung có dạng (u, -)
        if (pG->edges[e].u == u)
            deg_u++;
        // Nếu cung có dạng (-, u)
        if (pG->edges[e].v == u)
            deg_u++;
    }
    return deg_u;
}
int main(int argc, char **argv)
{
    Graph G;
    init_graph(&G, 4);
    // Gọi hàm add_edge()
    add_edge(&G, 1, 2);
    add_edge(&G, 3, 4);
    // Kiểm tra hàm add_edge bằng cách in dữ liệu của đồ thị ra màn hình
    // 1. In số đỉnh, số cung của đồ thị ra màn hình
    printf("n = %d, m = %d\n", G.n, G.m);
    // 2. In các cung của đồ thị ra màn hình
    int e;
    for (e = 0; e < G.m; e++)
        printf("%d %d\n", G.edges[e].u, G.edges[e].v);
    return 0;
}