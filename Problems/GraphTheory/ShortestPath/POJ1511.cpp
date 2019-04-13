#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXV=3e6+5,MAXE=MAXV;
typedef long long ll;
typedef pair<int,ll> pil;
const ll INF=0x5f5f5f5f5f5f5f5f;
ll dis[2][MAXV];
struct cmp
{
    bool operator()(const pil &a,const pil &b) { return a.second>b.second; }
};
struct Graph
{
    int top,head[MAXV],tmp[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,ll _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,ll l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    void swap(int v)
    {
        memset(tmp,-1,sizeof(tmp));
        for(int fr=1,to;fr<=v;++fr)
        {
            for(int i=head[fr];~i;i=head[fr])
            {
                to=edges[i].to;
                head[fr]=edges[i].last;
                edges[i].set(fr,tmp[to],edges[i].l);
                tmp[to]=i;
            }
        }
        for(int i=1;i<=v;++i) head[i]=tmp[i];
    }

    bool vis[MAXV];
    void Dij(int start,int v,ll* dis)
    {
        fill(dis+1,dis+v+1,INF);
        memset(vis,0,sizeof(vis));
        priority_queue<pil,vector<pil>,cmp> q;
        q.push(pil(start,0));
        dis[start]=0;
        int fr,to;
        ll d;
        while(!q.empty())
        {
            fr=q.top().first,q.pop();
            if(vis[fr]) continue;
            vis[fr]=1;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(vis[to]) continue;
                d=dis[fr]+edges[i].l;
                if(d<dis[to]) dis[to]=d,q.push(pil(to,dis[to]));
            }
        }
    }
} G;


int main()
{
    int T,v,e;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&v,&e);
        G.init();
        ll l;
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d %lld",&fr,&to,&l);
            G.add(fr,to,l);
        }
        G.Dij(1,v,dis[0]);
        G.swap(v);
        G.Dij(1,v,dis[1]);
        ll ans=0;
        for(int i=2;i<=v;++i)
            ans+=dis[0][i]+dis[1][i];
        printf("%lld\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr09 21:16:05	problem:POJ1511
输出没有用lld😭
还好卡的不久
跟POJ3268一样对图进行转置，但是数据范围大了很多
这里第一次写向前星的转置
=======================================*/