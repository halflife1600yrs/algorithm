#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
int v, e;
struct Edge
{
    int to, lenz, last;
    Edge()
        : to(0), lenz(0), last(0){};
    Edge(int a, int b, int c = 0)
        : to(a), lenz(b), last(c){};
    friend bool operator<(Edge a, Edge b) { return a.lenz > b.lenz; }
    void set(int _to, int _lenz, int _last) { to = _to, lenz = _lenz, last = _last; }
};
Edge edges[10005];
int vis[105], dis[105], head[105], top;

void addedg(int fr, int to, int lenz)
{
    edges[top].set(to, lenz, head[fr]), head[fr] = top++;
}

int diji()
{
    priority_queue<Edge> Que;
    while(!Que.empty()) Que.pop();
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(vis));
    dis[1] = 0;
    Que.push(Edge(1, 0));
    int fr, to;
    while(!Que.empty())
    {
        fr = Que.top().to, Que.pop();
        if(vis[fr]) continue; //一个点可能多次入队，一次距离大一次距离小
        vis[fr] = 1;
        for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
        {
            to = edges[addr].to;
            if(vis[to]) continue;
            int newdis = edges[addr].lenz + dis[fr];
            if(dis[to] > newdis) dis[to] = newdis, Que.push(Edge(to, newdis));
        }
    }
    return dis[v];
}

int main()
{
    while(~scanf("%d %d", &v, &e), v && e)
    {
        int a, b, c;
        memset(head, -1, sizeof(head)); //点号从1开始
        top = 0;
        for(int i = 0; i < e; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            addedg(a, b, c);
            addedg(b, a, c);
        }
        printf("%d\n", diji());
    }
    return 0;
}

/*=======================================
added at 2018年10月29日 21:00:46	problem:HDU2544
diji模板题
6 9
1 2 6
1 3 3
2 3 2
2 4 5
3 4 3
3 5 4
4 5 2
4 6 3
5 6 5
8 13
1 2 12
1 3 12
1 4 13
2 3 16
3 5 18
3 6 12
4 6 11
4 7 26
5 6 12
5 8 16
6 8 30
6 7 6
7 8 25

--9 46
=======================================*/