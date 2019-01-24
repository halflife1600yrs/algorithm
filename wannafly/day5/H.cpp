#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl

using namespace std;

const int sz = 1005;
int A[sz], B;
struct Tree
{
    int top, head[sz];
    int vis[sz], sons[sz];
    struct Node
    {
        int to, last;
        void set(int _to, int _last)
        {
            to = _to, last = _last;
        }
    } nodes[sz];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add_edge(int fr, int to)
    {
        debug2(to, top);
        nodes[top].set(to, head[fr]), head[fr] = top++;
    }
    int get_A(int root)
    {
        memset(vis, 0, sizeof(vis));
        memset(sons, 0, sizeof(sons));
        for(int i = 1; i <= 7; ++i) printf("%d ", sons[i]);
        printf("\n");
        return Dfs(root);
    }
    int Dfs(int root)
    {
        debug1(root);
        vis[root] = 1;
        int ans = 0, num = 0, to;
        for(int addr = head[root]; addr != -1; addr = nodes[addr].last)
        {
            to = nodes[addr].to;
            if(!vis[to])
            {
                num++;
                ans += Dfs(to);
                num += sons[to] + 1;
                ans += sons[to] + 1;
            }
            // debug2(addr, to);
        }
        sons[root] = num;
        return ans;
    }
} baset;

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int n, m;
    while(~scanf("%d %d", &n, &m))
    {
        int a, b;
        baset.init();
        for(int i = 0; i < m; ++i)
        {
            scanf("%d %d", &a, &b);
            baset.add_edge(a, b);
            baset.add_edge(b, a);
        }
        printf("%d\n", baset.get_A(1));
    }
    return 0;
}