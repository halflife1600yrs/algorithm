#include <bits/stdc++.h>

using namespace std;

const int MAXV=2e5+5,MAXE=(1e6+MAXV)*2;
int dis[MAXV];

typedef pair<int, int> pii;
struct cmp
{
    bool operator()(const pii& a, const pii& b) { return a.second > b.second; }
};
namespace G
{
    struct Edge
    {
        int to, last;
        int l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    bool vis[MAXV];

    void dijkstra(int start)
    {
        memset(dis, 0x7f, sizeof(dis));
        // memset(vis, 0, sizeof(vis));
        priority_queue<pii, vector<pii>, cmp> q;
        dis[start] = 0;
        q.push(pii(start, 0));
        int fr, to;
        while(!q.empty())
        {
            fr = q.top().first, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                int d = dis[fr] + edges[i].l;
                if(d < dis[to]) dis[to] = d, q.push(pii(to, d));
            }
        }
    }
}

int main()
{
    int v,e,k,st,en;
    scanf("%d %d %d",&v,&e,&k);
    scanf("%d %d",&st,&en);
    G::init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G::add(fr,to,l);
        G::add(to,fr,l);
        for(int j=1;j<=k;++j)
        {
            G::add((j-1)*v+fr,j*v+to,0);
            G::add((j-1)*v+to,j*v+fr,0);
            G::add(j*v+fr,j*v+to,l);
            G::add(j*v+to,j*v+fr,l);
        }
    }
    G::dijkstra(st);
    int ans=0x7f7f7f7f;
    for(int i=0;i<=k;++i)
    {
        if(dis[i*v+en]<ans) ans=dis[i*v+en];
    }
    printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-07 21:51:48	P4568
分层图模板题
k次对边操作应该是k+1层,数组大小要注意
==================================================================*/