#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
int nb_u;
typedef struct{
    int n,m;
    int A[max][max];
}Graph;

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

int adjacent(Graph *pG, int u, int v){
    return pG->A[u][v] > 0;
}

typedef struct{
    ElementType data[max];
    int top_idx;
}Stack;

//kkhởi tạo hàm rỗng
void make_null_stack(Stack *pS){
    pS->top_idx = -1;
}

//thêm phần tử u vào đỉnh ngăn xếp
void push(Stack *pS, ElementType u){
    pS->top_idx++;
    pS->data[pS->top_idx] = u;
}

//xem phần từ trên đầu đỉnh ngăn xếp
ElementType top(Stack *pS){
    return pS->data[pS->top_idx];
}

//xóa phần tử trên đỉnh ngăn xếp
void pop(Stack *pS){
    pS->top_idx--;
}

// kiểm tra ngăn xếp rỗng 
int empty(Stack *pS){
    return pS->top_idx == -1;
}

//duyệt đồ thị theo chiềuu sâu
void DFS(Graph *pG, int s){
    Stack S;
    make_null_stack(&S);

    //đưa s vào S, bắt đầu duyệt từ đỉnh s
    push(&S, s);

    //vòng lặp chính dùng để duyệt
    while (!empty(&S)){
        //3a lấy phần tử trên đỉnh S ra
        int u = top(&S);
        pop(&S);
        if(mark[u] != 0)// đã duyệt qua u rồi bỏ qua
            continue;
        // printf("%d\n",u);
        mark[u] = 1;// đánh dấu đã duyệt
        nb_u ++;

        //3b xét các đỉnh kề của u, đưa vào trong stack
        for(int v=1; v <= pG->n; v++){
            if(adjacent(pG,u,v)&& mark[v] == 0)
                push(&S,v);
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
    //khởi tạo mảng mark[u]=0
    for (int u = 1; u <= G.n; u++)
        mark[u] = 0;

    nb_u =0;
    int s;
    scanf("%d",&s);
    DFS(&G,s);
    printf("%d",nb_u);
    return 0;
}

/*
	
4 3
2 1
1 3
2 4
3
*/