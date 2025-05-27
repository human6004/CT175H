#include <bits/stdc++.h>
using namespace std;
// input
/*
9 9
1 2
1 3
1 5
2 4
3 6
3 7
3 9
5 8
8 9
*/
int n, m; // n: dinh, m: canh
vector<int> adj[1001];
bool visited[1001]; // kiem tra dinh nao do co duoc tham hay chua
void inp()
{ // chuyen danh sach canh sang danh sach ke
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y ; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(visited, false, sizeof(visited));
}
void dfs(int u)
{
    cout << u << " ";
    // danh dau la u da duoc tham
    visited[u] = true;
    for(int v : adj[u]){
        if(!visited[v]){
            dfs(v);
        }
    }
}
int main()
{
    inp();
    dfs(1);
}