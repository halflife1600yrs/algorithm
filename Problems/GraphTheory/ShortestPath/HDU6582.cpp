#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;
const int MAXV=2e4+5,MAXE=MAXV;
const ll INF=0x7f7f7f7f7f7f7f7f;
int v,e;

struct Graph
{
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE<<1];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, ll l)
    {
        // debug2(fr,to);
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
                if(depth[to] == -1 && edges[i].l > 0ll)
                    depth[to] = depth[fr] + 1, q.push(to);
            }
        }
        return depth[end] != -1;
    }

    ll dfs(int fr, int end, ll addflow = INF)
    {
        if(fr == end) return addflow;
        ll tf = 0, add;
        int d = depth[fr] + 1, to;
        for(int i = head[fr]; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] == d && edges[i].l > 0ll)
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
                if(d < dis[to]) dis[to] = d, q.push(pii(to, d));
            }
        }
    }

    void getShortestPaths()
    {
        for(int fr=1;fr<=v;++fr)
        {
            for(int j=head[fr],to;~j;j=edges[j].last)
            {
                to=edges[j].to;
                if(dis[fr]+edges[j].l==dis[to]) G2.add(fr,to,edges[j].l),G2.add(to,fr,0);
            }
        }
    }
} G1;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&v,&e);
        G1.init();
        int fr,to;
        ll l;
        for(int i=0;i<e;++i)
        {
            scanf("%d %d %lld",&fr,&to,&l);
            G1.add(fr,to,l);
        }
        G1.dijkstra(1);
        G2.init();
        G1.getShortestPaths();
        printf("%lld\n",G2.dinic(1,v));
    }
    return 0;
}

/*==================================================================
added at 2019-07-22 13:05:05	2019HDU暑假多校1E
最短路+网络流
==================================================================*/