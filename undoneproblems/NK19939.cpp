#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1000,MAXE=4*(1e5+5);
ll INF=0x7f7f7f7f7f7f7f7f;
int v,e,cap[MAXV];

struct Graph
{
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, ll l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
};

struct DINIC : Graph
{
    int depth[MAXV];
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
                if(depth[to] == -1 && edges[i].l > 0)
                    depth[to] = depth[fr] + 1, q.push(to);
            }
        }
        return depth[end] > 0;
    }

    ll dfs(int fr, int end, ll addflow = INF)
    {
        if(fr == end) return addflow;
        int to, d = depth[fr] + 1;
        ll tf=0,add;
        for(int i = head[fr]; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] == d && edges[i].l > 0)
            {
                add = dfs(to, end, min(addflow - tf, edges[i].l));
                edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
            }
        }
        if(!tf) depth[fr] = -1; // 因为是多次dfs增广,不能增广的点标记深度为-1
        return tf;
    }

    ll dinic(int start, int end)
    {
        ll ans = 0;
        while(bfs(start, end)) ans += dfs(start, end);
        return ans;
    }
} G2;


typedef pair<int, ll> pii;
struct cmp
{
    bool operator()(const pii& a, const pii& b) { return a.second > b.second; }
};

struct DIJKSTRA : Graph
{
    ll dis[MAXV];
    bool vis[MAXV];

    void dijkstra(int start)
    {
        memset(dis, 0x7f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        priority_queue<pii, vector<pii>, cmp> q;
        dis[start] = 0;
        q.push(pii(start, 0));
        int fr, to;
        ll d;
        while(!q.empty())
        {
            fr = q.top().first, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                d = dis[fr] + edges[i].l;
                // 这里也可以用来处理最小路径上的最大边或最大路径上的最小边
                // 求最小路径上最大边时,优先队列cmp不变,上句改为d=max(dis[fr],edges[i].l)
                // 同时下一句应该改为d更大时更新
                if(d < dis[to]) dis[to] = d, q.push(pii(to, d));
            }
        }
    }

    void getShortestPaths()
    {
        for(int i=1;i<=v;++i)
            for(int j=head[i];~j;j=edges[j].last)
                if(dis[i]+edges[j].l==dis[edges[j].to])
                    G2.add(i+v,j,INF),G2.add(j,i+v,0);
    }
} G1;

int main()
{
    scanf("%d %d",&v,&e);
    G1.init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G1.add(fr,to,l),G1.add(to,fr,l);
    }
    G2.init();
    for(int i=1;i<=v;++i)
    {
        scanf("%d",&cap[i]);
        G2.add(i,i+v,cap[i]),G2.add(i+v,i,0);
    }
    G1.getShortestPaths();
    return 0;
}