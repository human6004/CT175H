#include <stdio.h>

#define MAXM 500
#define MAXN 100
#define oo 999999
#define NO_EDGE -999999

typedef struct {
    int u, v;
    int w;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAXM];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w) {
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;

    pG->m++;
}


int pi[MAXN];
int p[MAXN];

int BellmanFord(Graph *pG, int s) {
	int u, v, w, it, k;
	for (u = 1; u <= pG->n; u++) {
		pi[u] = oo;
	}
	pi[s] = 0;
	p[s] = -1; //trước đỉnh s không có đỉnh nào cả

	// lặp n-1 lần
	for (it = 1; it < pG->n; it++) {
		// Duyệt qua các cung và cập nhật (nếu thoả)
		for (k = 0; k < pG->m; k++) {
			u = pG->edges[k].u;
			v = pG->edges[k].v;
			w = pG->edges[k].w;
			
			if (pi[u] == oo)    //chưa có đường đi từ s -> u, bỏ qua cung này
			    continue;
			    
			if (pi[u] + w < pi[v]) {
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	//Làm thêm 1 lần nữa để kiểm tra chu trình âm (nếu cần thiết)
	for (k = 0; k < pG->m; k++) {
		u = pG->edges[k].u;
		v = pG->edges[k].v;
		w = pG->edges[k].w;
		
		if (pi[u] == oo)    //chưa có đường đi từ s -> u, bỏ qua cung này
		    continue;
		    
		if (pi[u] + w < pi[v]) {
			return 1;
		}
	}
	return 0;
}



int main() {
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for (int e = 0; e < m; e++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    int s;
    scanf("%d", &s);
    
    if (BellmanFord(&G, s) == 1)
        printf("YES\n");
    else
        printf("NO\n");

    
    return 0;
}

// 4 4
// 1 2 1
// 2 3 -1
// 3 4 -1
// 4 1 -1
// 2