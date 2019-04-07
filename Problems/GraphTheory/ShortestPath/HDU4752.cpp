#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int MAXV=1e5+5,MAXE=1e5+5;
const int INF=0x7f7f7f7f;

int v,e,cost,layerv[MAXV],layer[MAXV]; //每层点数
bool extend[MAXV];

inline int layerNode(int x) { return v+x; }

struct cmp
{
    bool operator()(pii a,pii b)
    {
        return a.second>b.second;
    }
};

struct Graph
{
    int top,head[MAXV<<1],dis[MAXV<<1];
    bool vis[MAXV<<1];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE<<3];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    int Dij(int start,int end)
    {
        memset(dis,0x7f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        priority_queue<pii,vector<pii>,cmp> q;
        dis[start]=0;
        q.push(pii(start,0));
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
                // debug2(fr,to);
                newd=dis[fr]+edges[addr].l;
                if(newd<dis[to]) dis[to]=newd,q.push(pii(to,newd));
            }
        }
        return vis[end]?dis[end]:-1;
    }
} G;

void extendp(int p)
{
    if(!extend[p])
    {
        int l=layer[p];
        G.add(p,layerNode(l),0);
        if(layerv[l-1])
        {
            G.add(p,layerNode(l-1),cost);
            G.add(layerNode(l-1),p,cost);
        }
        if(layerv[l+1])
        {
            G.add(p,layerNode(l+1),cost);
            G.add(layerNode(l+1),p,cost);
        }
        extend[p]=1;
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d %d %d",&v,&e,&cost);
        G.init();
        memset(layerv,0,sizeof(layerv));
        memset(extend,0,sizeof(extend));
        for(int i=1,lay;i<=v;++i)
        {
            scanf("%d",&lay);
            layer[i]=lay;
            ++layerv[lay];
        }
        for(int i=1,fr,to;i<v;++i)
            if(layerv[i]&&layerv[i+1])
            {
                fr=layerNode(i),to=layerNode(i+1);
                G.add(fr,to,cost),G.add(to,fr,cost);
            }
        // disp(layerv,0,v+1);
        for(int i=0,fr,to,d;i<e;++i)
        {
            scanf("%d %d %d",&fr,&to,&d);
            G.add(fr,to,d),G.add(to,fr,d);
            extendp(fr),extendp(to);
        }
        extendp(1),extendp(v);
        printf("Case #%d: %d\n",_,G.Dij(1,v));
    }
    return 0;
}

/*=======================================
added at 2019.Apr03 11:11:45	problem:HDU4752
最短路
将每层抽象为1个点，然后每当连边时将点和层点相连
这里注意要和上下两层的层点连双向边，和本层的连单向边
层点之间也要连接防止否则没有边的情况会出错
=======================================*/