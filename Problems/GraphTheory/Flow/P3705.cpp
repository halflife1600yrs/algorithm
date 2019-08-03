#include <bits/stdc++.h>

using namespace std;

const int MAXN=105,MAXV=MAXN*2,MAXE=MAXV*MAXV*2+4*MAXV;
const double INF=1e18,EPS=5e-8,FIX=2e8;
int a[MAXN][MAXN],b[MAXN][MAXN];

int n;
int ans;
double cost;
int st, en;

namespace q
{
    const int top=MAXV*2;
    int data[top],s,t;
    void push(int x) { data[s==top-1?s=0,top-1:s++]=x; }
    int pop() { return data[t==top-1?t=0,top-1:t++]; }
}

namespace G
{
    int head[MAXV];
    int top;
    struct Edge
    {
        int to, last, c;
        double l;
        void set(int _to, int _last, double _l, int _c) { to = _to, last = _last, l = _l, c = _c; }
    } edges[MAXE << 1];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, double l, int c)
    {
        edges[top].set(to, head[fr], l, c);
        head[fr] = top++;
        edges[top].set(fr, head[to], -l, 0);
        head[to] = top++;
    }

    int prev[MAXV], pree[MAXV], minf[MAXV];
    bool vis[MAXV];
    double dis[MAXV];

    bool spfa()
    {
        fill(dis,dis+2*n+10,-INF);
        memset(vis, 0, sizeof(vis));
        memset(minf, 0x7f, sizeof(minf));
        pree[en]=-1;
        q::s=q::t=0;
        q::push(st);
        dis[st] = 0, vis[st] = 1;
        int fr, to;
        while (q::s!=q::t)
        {
            fr = q::pop();
            vis[fr] = 0;
            for (int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if (edges[i].c > 0 && dis[fr] + edges[i].l > dis[to])
                {
                    dis[to] = dis[fr] + edges[i].l;
                    minf[to] = min(minf[fr], edges[i].c);
                    prev[to] = fr;
                    pree[to] = i;
                    if (!vis[to])
                        q::push(to), vis[to] = 1;
                }
            }
        }
        return pree[en] != -1;
    }

    void dfs()
    {
        int cur = en, i, tmp = minf[en];
        while (cur != st)
        {
            i = pree[cur];
            edges[i].c -= tmp;
            edges[i ^ 1].c += tmp;
            cur = prev[cur];
        }
        ans += tmp;
        cost += dis[en];
    }

    void mcf()
    {
        ans = cost = 0;
        while (spfa())
            dfs();
    }
}

void rebuild(double c)
{
    G::init();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            G::add(i,j+n,a[i][j]-c*b[i][j]+FIX,1);
        G::add(st,i,0,1),G::add(i+n,en,0,1);
    }
}

bool work(double c)
{
    rebuild(c);
    G::mcf();
    if(cost-n*FIX<0) return 1;
    return 0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a[i][j]);
    double l=INF,r=-INF,tmp,mid;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&b[i][j]);
            tmp=1.0*a[i][j]/b[i][j];
            if(tmp>r) r=tmp;
            if(tmp<l) l=tmp;
        }
    st=0,en=2*n+1;
    while(abs(l-r)>EPS)
    {
        mid=(l+r)/2.0;
        if(work(mid))
        {
            r=mid;
        } else 
        {
            l=mid;
        }
    }
    printf("%.6lf\n",l);
    return 0;
}

/*==================================================================
added at 2019-08-03 19:55:26 H
01分数规划,用费用流做,对于负权边加上一个较大的值使其变为正权
==================================================================*/