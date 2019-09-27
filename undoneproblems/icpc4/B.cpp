#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1005,MAXE=MAXV*MAXV;
const ll INF=0x7f7f7f7f7f7f7f7f;
typedef pair<ll,int> pii;
int V,E,team[MAXV];

namespace G
{
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to, ll l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    ll dis[MAXV];
    bool vis[MAXV];
    ll dijkstra(int start)
    {
        fill(dis + 1, dis + V + 1, INF);
        fill(vis + 1, vis + V + 1, 0);
        priority_queue<pii, vector<pii>, greater<pii>> q;
        dis[start] = 0;
        q.push(pii(0, start));
        int fr, to;
        ll maxi=0;
        while(!q.empty())
        {
            fr = q.top().second, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            maxi=max(maxi,dis[fr]);
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                ll d = dis[fr] + edges[i].l;
                if(d < dis[to]) dis[to] = d, q.push(pii(d, to));
            }
        }
        return maxi;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&V,&E);
        int hero,k,c;
        scanf("%d %d %d",&hero,&k,&c);
        for(int i=0;i<k;++i) scanf("%d",&team[i]);
        G::init();
        for(int i=0,fr,to,l;i<E;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G::add(fr,to,l),G::add(to,fr,l);
        }
        ll ans1=G::dijkstra(hero);
        ++V;
        for(int i=0;i<k;++i)
            G::add(V,team[i],0);
        ll ans2=G::dijkstra(V);
        if(ans1<=ans2*c) printf("%lld\n",ans1);
        else printf("%lld\n",ans2);
    }
    return 0;
}