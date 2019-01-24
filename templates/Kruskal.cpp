#include <bits/stdc++.h>

using namespace std;

int v, e;
const int maxv = 5005, maxe = 200005;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int fr, to, v;
    void set(int _fr, int _to, int _v) { fr = _fr, to = _to, v = _v; }
};
bool cmp(Edge a, Edge b) { return a.v < b.v; }
struct Graph
{ //顶点从1开始记
    int top, u_set[maxv];
    Edge edges[maxe];
    void init() { top = 0; }
    void addedge(int fr, int to, int v) { edges[top++].set(fr, to, v); }
    int Kruskal()
    { //判断是否成环需要使用并查集
        for(int i = 1; i <= v; i++) u_set[i] = i;
        sort(edges, edges + e, cmp);
        int lenz = 0, ans = 0, fr, to, x, y;
        for(int i = 0; i < e; i++)
        {
            fr = edges[i].fr, to = edges[i].to;
            x = getf(fr), y = getf(to);
            if(x == y) continue;
            lenz++, ans += edges[i].v;
            u_set[y] = x;
        }
        if(lenz < v - 1) return -1;
        return ans;
    }
    int getf(int x)
    {
        if(u_set[x] == x) return x;
        return u_set[x] = getf(u_set[x]); //返回时需要更新,不更新可能被卡
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
        }
        int ans = g.Kruskal();
        if(ans == -1)
            printf("orz\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}

/*=======================================
最小生成树模板-kruskal
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3
- 7
=======================================*/