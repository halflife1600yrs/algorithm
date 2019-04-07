#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

typedef pair<int,int> pii;
const int MAXV=1005,MAXE=1e6+5,INF=0x7f7f7f7f;
struct cmp
{
    bool operator()(pii a,pii b) { return a.second<b.second; }
};
struct Graph
{
    int top,head[MAXV],dis[MAXV];
    bool vis[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    int Dij(int start,int end)
    {
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        priority_queue<pii,vector<pii>,cmp> q;
        dis[start]=INF;
        q.push(pii(start,INF));
        int fr,to;
        while(!q.empty())
        {
            fr=q.top().first,q.pop();
            if(vis[fr]) continue;
            vis[fr]=1;
            for(int addr=head[fr],newd;addr!=-1;addr=edges[addr].last)
            {
                to=edges[addr].to;
                if(vis[to]) continue;
                newd=min(dis[fr],edges[addr].l);
                if(newd>dis[to]) dis[to]=newd,q.push(pii(to,newd));
            }
        }
        return vis[end]?dis[end]:-1;
    }
} G;


int main()
{
    int v,e;
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d %d",&v,&e);
        G.init();
        for(int i=0,fr,to,l;i<e;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G.add(fr,to,l),G.add(to,fr,l);
        }
        printf("Scenario #%d:\n%d\n\n",_,G.Dij(1,v));
    }
    return 0;    
}

/*=======================================
added at 2019.Apr07 19:50:50	problem:POJ1797
最短路变式
路径最小边最大值
=======================================*/