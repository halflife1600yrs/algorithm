#include <bits/stdc++.h>

using namespace std;

const int maxv = 1005, maxe = 200005;
const int INF = 0x3f3f3f3f;

int path[maxv][maxv];
short repeat[maxv][maxv], dis[maxv][maxv];
struct Graph
{
    int v, e;
    int depth[maxv], head[maxv];
    bool vis[maxv];
    int top;
    struct Edge
    {
        int to, v, last;
        void set(int _to, int _v, int _last) { to = _to, v = _v, last = _last; }
        friend bool operator<(Edge a, Edge b) { return a.v > b.v; }
    } edges[maxe];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add_edge(int _fr, int _to, int _v)
    {
        edges[top].set(_to, _v, head[_fr]), head[_fr] = top++;
    }
    int Diji(int start, int end)
    {
        priority_queue<Edge> Q;
        while(!Q.empty()) Q.pop();
        memset(depth, 0x3f, sizeof(depth));
        memset(vis, 0, sizeof(vis));
        depth[start] = 0;
        Q.push({ start, 0, 0 });
        int fr, to;
        while(!Q.empty())
        {
            fr = Q.top().to, vis[fr] = 1, Q.pop();
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(vis[to]) continue;
                int newdis = edges[addr].v + depth[fr];
                if(depth[to] == newdis) path[fr][to] = newdis;
                if(depth[to] > newdis)
                {
                    depth[to] = newdis, Q.push({ to, newdis, 0 });
                    path[fr][to] = newdis;
                }
            }
        }
        return depth[end];
    }
    bool bfs(int start, int end)
    {
        queue<int> Q;
        while(!Q.empty()) Q.pop();
        memset(depth, -1, sizeof(depth));
        depth[start] = 0;
        Q.push(start);
        int fr, to;
        while(!Q.empty())
        {
            fr = Q.front(), Q.pop();
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(depth[to] == -1 && edges[addr].v > 0)
                    depth[to] = depth[fr] + 1, Q.push(to);
            }
        }
        return depth[end] > 0;
    }
    int dfs(int fr, int end, int maxflow)
    {
        if(fr == end) return maxflow;
        int usedflow = 0, to, cap;
        for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
        {
            to = edges[addr].to, cap = edges[addr].v;
            if(depth[to] == depth[fr] + 1 && cap > 0)
            {
                int tmp = dfs(to, end, min(cap, maxflow - usedflow));
                edges[addr].v -= tmp, edges[addr ^ 1].v += tmp, usedflow += tmp;
            }
        }
        if(!usedflow) depth[fr] = -1;
        return usedflow;
    }
    int Dinic(int start, int end)
    {
        int ans = 0;
        while(bfs(start, end))
        {
            ans += dfs(start, end, INF);
        }
        return ans;
    }
} chose, check;


int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int cas, start, end;
    for(scanf("%d", &cas); cas--;)
    {
        chose.init();
        check.init();
        scanf("%d %d", &chose.v, &chose.e);
        int a, b, c;
        memset(dis, 0x3f, sizeof(dis));
        memset(repeat, 0, sizeof(repeat));
        for(int i = 0; i < chose.e; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            chose.add_edge(a, b, c);
            if(dis[a][b] == c) repeat[a][b]++;
            if(dis[a][b] > c) repeat[a][b] = 1, dis[a][b] = c;
        }
        scanf("%d %d", &start, &end);
        memset(path, 0, sizeof(path));
        chose.Diji(start, end);
        for(int i = 1; i <= chose.v; i++)
            for(int j = 1; j <= chose.v; j++)
                if(path[i][j] == chose.depth[j])
                {
                    check.add_edge(i, j, repeat[i][j]);
                    check.add_edge(j, i, 0);
                }
        printf("%d\n", check.Dinic(start, end));
    }
    return 0;
}
/*=======================================
added at 2018年10月30日 20:59:46	problem:HDU3416
最短路+网络流
应该用邻接矩阵做，用邻接表太慢了
3
7 8
1 2 1
1 3 1
2 4 1
3 4 1
4 5 1
4 6 1
5 7 1
6 7 1
1 7

6 7
1 2 1
2 3 1
1 3 3
3 4 1
3 5 1
4 6 1
5 6 1
1 6

2 2
1 2 1
1 2 2
1 2
-- 2 1 1
=======================================*/