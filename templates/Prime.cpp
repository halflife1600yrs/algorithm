#include <bits/stdc++.h>

using namespace std;

int v, e;
const int maxv = 5005, maxe = 200000;
const int INF = 0x3f3f3f3f;
struct Graph
{ //顶点从1开始记
    int head[maxv], top;
    int dis[maxv];
    bool chosen[maxv];
    struct Edge
    {
        int to, v, last;
        void set(int _to, int _v, int _last) { to = _to, v = _v, last = _last; }
    } edges[maxe << 1];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void addedge(int fr, int to, int v)
    {
        edges[top].set(to, v, head[fr]);
        head[fr] = top++;
    }
    int Prim()
    {
        memset(dis, 0x3f, sizeof(dis));
        memset(chosen, 0, sizeof(chosen));
        int lenz = 0, ans = 0, mini, cur = 1, to;
        dis[1] = 0;
        while(lenz < v)
        {
            for(int i = head[cur]; i != -1; i = edges[i].last)
            {
                to = edges[i].to;
                if(!chosen[to]) dis[to] = min(dis[to], edges[i].v);
            }
            mini = INF, to = -1;
            for(int i = 1; i <= v; i++)
                if(!chosen[i] && dis[i] < mini) mini = dis[i], to = i;
            if(to == -1) return -1;
            chosen[to] = 1, cur = to, ans += mini, lenz++;
        }
        return ans;
    }
} g;

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    while(~scanf("%d %d", &v, &e))
    {
        g.init();
        int a, b, c;
        for(int i = 0; i < e; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            g.addedge(a, b, c);
            g.addedge(b, a, c);
        }
        int ans = g.Prim();
        if(ans == -1)
            printf("orz\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}

/*=======================================
最小生成树模板-prime
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3
- 7
=======================================*/