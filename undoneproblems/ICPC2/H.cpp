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
typedef pair<ll,int> pii;
const int MAXV=305,MAXE=505;
const ll INF=0x7f7f7f7f7f7f7f7f;
int V,E;

namespace G
{
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head, head + V + 1, -1); }
    void add(int fr, int to, ll l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    ll dis[MAXV];
    int cnt[MAXV];
    bool vis[MAXV];
    bool spfa(int st)
    {
        fill(dis, dis + V + 1, INF);
        fill(vis, vis + V + 1, 0);
        fill(cnt, cnt + V + 1, 0);
        queue<int> q;
        dis[st] = 0;
        q.push(st);
        cnt[st] = 1;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                ll d = dis[fr] + edges[i].l; // 这里注意即使在队列中也要更新
                if(d < dis[to])
                {
                    dis[to] = d;
                    if(vis[to]) continue;
                    vis[to] = 1, ++cnt[to];
                    if(cnt[to] > V) return 1;
                    q.push(to);
                }
            }
        }
        return 0;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&V,&E);
        int fr,to,l;
        G::init();
        for(int i=0;i<E;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G::add(fr,to,l);
        }
        for(int i=0,st,en;i<6;++i)
        {
            scanf("%d %d",&st,&en);
            G::spfa(en);
            ll tmp=-G::dis[st];
            printf("%lld\n",tmp);
            G::add(st,en,tmp);
        }
    }
    return 0;
}