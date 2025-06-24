#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define oo 1000000

int n, m;        // kich thuoc ma tran
int a[100][100]; // ma trận lưu giá trị các ô
int pi[MAX_N];   // pi[u]: chi phí nhỏ nhất từ ô đầu đến ô thứ u
int p[MAX_N];    // p[u]: lưu đỉnh cha của u trên đường đi ngắn nhất
int mark[MAX_N]; // mark[u]: đánh dấu đỉnh u đã xét xong

int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1}; // trên, dưới,trái phải

void Dijkstra(int s)
{
    int N = n * m; // dien tích của ma trận n hàng m cột
    for (int i = 0; i < N; i++)
    {
        pi[i] = oo;
        mark[i] = 0;
        p[i] = -1;
    }
    pi[s] = 0; // chi phi bat dau bang gia tri o 0,0
    for (int it = 0; it < N; it++)
    {
        int u = -1, mn = oo;
        for (int i = 0; i < N; i++)
            if (!mark[i] && pi[i] < mn)
            {
                mn = pi[i];
                u = i;
            }
        if (u < 0) // nếu đã duyệt xong hết ròi thì break
            break;
        mark[u] = 1;    // đánh dấu đã duyệt
        int ux = u / m; // chỉ số hàng x
        int uy = u % m; // chỉ số cột y
        for (int k = 0; k < 4; k++)
        { // dò tìm all ô bên cạnh chưa duyệt
            int Vx = ux + dx[k], Vy = uy + dy[k];
            // if (Vx >= 0 && Vx < n && Vy >= 0 && Vy < m)
            //     continue;
            if (Vx < 0 || Vx >= n || Vy < 0 || Vy >= m)
                continue;

            int v = Vx * m + Vy; // địa chỉ ô thứ v
            int w = a[Vx][Vy];   // giá trị của ô đó
            if (!mark[v] && pi[u] + w < pi[v])
            {
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    Dijkstra(0);
    int t = (n - 1) * m + (m - 1);
    printf("%d\n", pi[t]);

    return 0;
}