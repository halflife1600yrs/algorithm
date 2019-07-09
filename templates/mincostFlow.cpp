#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5050, MAXE = 50005, INF = 0x7f7f7f7f;
int v, e;
int ans, cost;
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
        memset(dis, 0x7f, sizeof(dis)); // 最大费用的时候下面要改>号,这里要用0x80初始化为负值
        memset(vis, 0, sizeof(vis));
        memset(minf, 0x7f, sizeof(minf));
        queue<int> q;
        q.push(start);
        dis[start] = 0, vis[start] = 1;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(edges[i].c > 0 && dis[fr] + edges[i].l < dis[to])
                {
                    dis[to] = dis[fr] + edges[i].l;
                    minf[to] = min(minf[fr], edges[i].c);
                    prev[to] = fr;
                    pree[to] = i;
                    if(!vis[to]) q.push(to), vis[to] = 1;
                }
            }
        }
        return dis[end] != INF; // 这里也可以用pree[end]!=-1来判断,但是要初始化pree
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
        cost += dis[end] * tmp;
    }
    void mcf()
    {
        ans = cost = 0;
        while(spfa()) dfs();
    }
} G;

int main()
{
    scanf("%d %d %d %d", &v, &e, &G.start, &G.end);
    G.init();
    for(int i = 0, fr, to, c, l; i < e; ++i)
    {
        scanf("%d %d %d %d", &fr, &to, &c, &l);
        G.add(fr, to, l, c);
    }
    G.mcf();
    printf("%d %d\n", ans, cost);
    return 0;
}

/*=======================================
added at 2019.May06 18:59:34	problem:P3381
最小费用最大流模板题
=======================================*/