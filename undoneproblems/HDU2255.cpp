#include <bits/stdc++.h>

using namespace std;

const int MAXV=305,MAXE=MAXV*4,INF=0x7f7f7f7f;
int v, e;
int ans, cost;
int maxi;
struct G
{
    int head[MAXV];
    int top;
    struct Edge
    {
        int to, last, l, c;
        void set(int _to, int _last, int _l, int _c) { to = _to, last = _last, l = _l, c = _c; }
    } edges[MAXE << 1];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to, int l, int c)
    {
        edges[top].set(to, head[fr], l, c);
        head[fr] = top++;
        edges[top].set(fr, head[to], -l, 0);
        head[to] = top++;
    }
    int start, end;
    int dis[MAXV], prev[MAXV], pree[MAXV], minf[MAXV];
    bool vis[MAXV];
    bool spfa()
    {
        memset(dis, 0, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        memset(minf, 0x7f, sizeof(minf));
        queue<int> q;
        q.push(start);
        dis[start] = 0, vis[start] = 1;
        minf[start] = INF;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(edges[i].c > 0 && dis[fr] + edges[i].l > dis[to])
                {
                    dis[to] = dis[fr] + edges[i].l;
                    minf[to] = min(minf[fr], edges[i].c);
                    prev[to] = fr;
                    pree[to] = i;
                    if(!vis[to]) q.push(to), vis[to] = 1;
                }
            }
        }
        return dis[end] != 0;
    }
    void dfs()
    {
        int cur = end;
        int i, tmp = minf[end];
        while(cur != start)
        {
            i = pree[cur];
            edges[i].c -= tmp;
            edges[i ^ 1].c += tmp;
            cur = prev[cur];
        }
        ans += tmp;
        cost += dis[end] * tmp - 2;
    }
    void mcf()
    {
        ans = cost = 0;
        while(spfa()) dfs();
    }
} G;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        G.init();
        G.start=2*n+1,G.end=2*n+2;
        for(int i=1;i<=n;++i)
        {
            G.add(G.start,i,1,1);
            G.add(n+i,G.end,1,1);
        }
        for(int i=1,l;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&l);
                G.add(i,n+j,l,1);
            }
        }
        G.mcf();
        printf("%d\n",cost);
    }
    return 0;
}