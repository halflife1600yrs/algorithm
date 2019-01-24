#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl

const int maxv = 505, maxe = 250005;
int v, e;
int teams[maxv];
bool cmp(int a, int b) { return a > b; }
struct Graph
{
    int top, indgre[maxv], head[maxv];
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[maxe];
    void init() { top = 0, memset(indgre, 0, sizeof(indgre)), memset(head, -1, sizeof(head)); }
    void addedge(int fr, int to)
    {
        // debug2(fr, to);
        edges[top].set(to, head[fr]);
        head[fr] = top++, ++indgre[to];
    }
    int TopSort(int* ans)
    {
        priority_queue<int, vector<int>, greater<int>> q;
        while(!q.empty()) q.pop();
        int fr, to, num = 0;
        for(int i = 1; i <= v; ++i)
            if(!indgre[i]) q.push(i);
        while(!q.empty())
        {
            fr = q.top(), q.pop(), ans[num++] = fr;
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(!--indgre[to]) q.push(to);
            }
        }
        return num == v;
    }
} G;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    while(~scanf("%d %d", &v, &e))
    {
        int a, b;
        G.init();
        for(int i = 0; i < e; ++i)
        {
            scanf("%d %d", &a, &b);
            G.addedge(a, b);
        }
        // for(int i = 1; i <= v; ++i) printf("%d ", G.indgre[i]);
        // printf("\n");
        if(G.TopSort(teams))
        {
            for(int i = 0; i < v - 1; ++i)
                printf("%d ", teams[i]);
            printf("%d\n", teams[v - 1]);
        }
    }
    return 0;
}