#include <bits/stdc++.h>

using namespace std;

const int MAXV = 205, MAXE = 3000, INF = 0x7f7f7f7f;
int v, e;
struct Graph
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE << 1];
    
    int top, head[MAXV], depth[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    bool bfs(int start, int end)
    {
        queue<int> q;
        memset(depth, -1, sizeof(depth));
        q.push(start);
        depth[start] = 0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(depth[to] != -1 || edges[i].l <= 0) continue;
                depth[to] = depth[fr] + 1;
                q.push(to);
            }
        }
        return depth[end] > 0;
    }

    int dfs(int fr, int end, int addflow = INF)
    {
        if(fr == end) return addflow;
        int tf = 0, to;
        for(int i = head[fr]; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] != depth[fr] + 1 || edges[i].l <= 0) continue;
            int add = dfs(to, end, min(addflow - tf, edges[i].l));
            edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
        }
        if(tf == 0) depth[fr] = -1; // 因为是多次dfs增广,不能增广的点标记深度为-1
        return tf;
    }

    int dinic(int start, int end)
    {
        int ans = 0;
        while(bfs(start, end)) ans += dfs(start, end);
        return ans;
    }
} G;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int start,end;
    scanf("%d %d %d %d",&v,&e,&start,&end);
    G.init();
    for(int i=1;i<=v;++i)
    {
        G.add(i,i+v,1);
        G.add(i+v,i,0);
    }
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        G.add(fr+v,to,INF);
        G.add(to,fr+v,0);
        G.add(to+v,fr,INF);
        G.add(fr,to+v,0);
    }
    printf("%d\n",G.dinic(start+v,end));
    return 0;
}