#include <bits/stdc++.h>

using namespace std;

const int maxv = 10005, maxe = 200010;
const int INF = 0x3f3f3f3f;
int v, e;
struct Graph
{
    int head[maxv];
    int start, end, top;
    int depth[maxv];
    struct Edge
    {
        int to, cap, last;
        void set(int _to, int _cap, int _last) { to = _to, cap = _cap, last = _last; }
    } edges[maxe];
    void init() { top = 0, fill(head, head + v + 1, -1); }
    void add_edge(int fr, int to, int cap) { edges[top].set(to, cap, head[fr]), head[fr] = top++; }
    bool bfs()
    {
        queue<int> Q;
        while(!Q.empty()) Q.pop();
        fill(depth, depth + v + 1, -1);
        Q.push(start);
        depth[start] = 0;
        while(!Q.empty())
        {
            int fr = Q.front(), addr = head[fr];
            Q.pop();
            while(addr != -1)
            {
                int to = edges[addr].to;
                if(depth[to] == -1 && edges[addr].cap > 0)
                {
                    depth[to] = depth[fr] + 1;
                    Q.push(to);
                }
                addr = edges[addr].last;
            }
        }
        return depth[end] > 0;
    }
    int dfs(int fr, int addflow = INF)
    {
        if(fr == end) return addflow;
        int addr = head[fr];
        int tf = 0;
        while(addr != -1)
        {
            int to = edges[addr].to, cap = edges[addr].cap;
            if(depth[to] == depth[fr] + 1 && cap > 0)
            {
                int add = dfs(to, min(addflow - tf, cap));
                edges[addr].cap -= add, edges[addr ^ 1].cap += add, tf += add;
            }
            addr = edges[addr].last;
        }
        if(tf == 0) depth[fr] = -1;
        return tf;
    }
    int Dinic()
    {
        int ans = 0;
        while(bfs())
            ans += dfs(start);
        return ans;
    }
} graph;

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    while(~scanf("%d %d %d %d", &v, &e, &graph.start, &graph.end))
    {
        int a, b, c;
        graph.init();
        for(int i = 0; i < e; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            graph.add_edge(a, b, c);
            graph.add_edge(b, a, 0);
        }
        printf("%d\n", graph.Dinic());
    }
    return 0;
}

/*=======================================
addred at 2018年11月04日 20:30:07	problem:HDU3549
网络流模板题
=======================================*/
/*=======================================
added at 2018年11月29日 20:35:51	problem:P3376
t了一个下午然后转而用这个模板去做洛谷模板题的时候发现是因为maxe没有*2导致的错误
血的教训
6 9 1 6
4 2 4
4 3 4
4 6 3
3 1 1
1 4 4
4 1 3
3 6 5
5 6 6
6 3 3
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40

-- 4 50
=======================================*/