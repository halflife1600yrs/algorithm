#include <bits/stdc++.h>

using namespace std;

const int maxv = 10005, maxe = 200010;
const int INF = 0x3f3f3f3f;

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
    void init() { top = 0, fill(head, head + v + 1, -1); }
    void add_edge(int fr, int to, int v)
    {
        edges[top].set(to, v, head[fr]), head[fr] = top++;
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
            fr = Q.top().to, Q.pop();
            if(vis[fr]) continue;
            vis[fr] = 1;
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(vis[to]) continue;
                int newdis = edges[addr].v + depth[fr];
                if(depth[to] > newdis) depth[to] = newdis, Q.push({ to, newdis, 0 });
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
                if(depth[to] == -1 && edges[addr].v > 0) depth[to] = depth[fr] + 1, Q.push(to);
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
        while(bfs(start, end)) ans += dfs(start, end, INF);
        return ans;
    }
} graph;

int main()
{
    return 0;
}
