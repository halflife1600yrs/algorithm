#include <bits/stdc++.h>

using namespace std;

typedef int ll;
typedef pair<ll, int> pii;
const int MAXV=1e3+5,MAXE=2e4+5,INF=0x7f7f7f7f;
int V,E,land[MAXV][MAXV];
int p[105],q[105];
long long dp[2][105][105];

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
    bool vis[MAXV];
    void dijkstra(int start)
    {
        fill(dis, dis + V + 1, INF);
        fill(vis, vis + V + 1, 0);
        priority_queue<pii, vector<pii>, greater<pii>> q;
        dis[start] = 0;
        q.push(pii(0, start));
        int fr, to;
        while(!q.empty())
        {
            fr = q.top().second, q.pop();
            if(vis[fr]) continue;
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                ll d = dis[fr] + edges[i].l;
                if(d < dis[to]) dis[to] = d, q.push(pii(d, to));
            }
        }
    }
}

int get(int fr,int to)
{
    if(!land[fr][to])
    {
        G::dijkstra(fr);
        for(int i=1;i<=V;++i) land[i][fr]=land[fr][i]=G::dis[i];
    }
    return land[fr][to];
}

int main()
{
    scanf("%d %d",&V,&E);
    G::init();
    for(int i=0,fr,to,l;i<E;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G::add(fr,to,l),G::add(to,fr,l);
    }
    int a,b;
    memset(dp,0x7f,sizeof(dp));
    scanf("%d",&a);
    for(int i=1;i<=a;++i) scanf("%d",&p[i]);
    scanf("%d",&b);
    for(int i=1;i<=b;++i) scanf("%d",&q[i]);
    dp[0][1][0]=dp[1][0][1]=0;
    for(int i=0;i<=a;++i)
    {
        for(int j=0;j<=b;++j)
        {
            if(dp[0][i][j]<0x7f7f7f7f7f7f7f7f)
            {
                dp[0][i+1][j]=min(dp[0][i+1][j],dp[0][i][j]+get(p[i],p[i+1]));
                dp[1][i][j+1]=min(dp[1][i][j+1],dp[0][i][j]+get(p[i],q[j+1]));
            }
            if(dp[1][i][j]<0x7f7f7f7f7f7f7f7f)
            {
                if(land[q[j]][q[j+1]]<INF) dp[1][i][j+1]=min(dp[1][i][j+1],dp[1][i][j]+get(q[j],q[j+1]));
                if(land[q[j]][p[i+1]]<INF) dp[0][i+1][j]=min(dp[0][i+1][j],dp[1][i][j]+get(q[j],p[i+1]));
            }
        }
    }
    printf("%lld\n",min(dp[0][a][b],dp[1][a][b]));
    return 0;
}

/*==================================================================
added at 2019-09-28 12:10:29 NK1090B
跟交换教室有点像
INF设小了,dp不应该和dis使用一样的INF
==================================================================*/