#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int,int> pii;
const int MAXV=3e4+5,MAXE=15e4+5,INF=0x7f7f7f7f;
bool vis[MAXV];
int dis[MAXV];
struct Graph
{
    int top,head[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int v)
    {
        edges[top].set(to,head[fr],v);
        head[fr]=top++;
    }
    void Dij(int start);
} G;
struct cmp
{
    bool operator()(const pii& a,const pii& b) { return a.second>b.second; }
};
void Graph::Dij(int start)
{
    memset(dis,0x7f,sizeof(dis));
    priority_queue<pii,vector<pii>,cmp> q;
    dis[start]=0;
    q.push(pii(start,0));
    int fr,to;
    while(!q.empty())
    {
        fr=q.top().first,q.pop();
        if(vis[fr]) continue;
        vis[fr]=1;
        for(int i=head[fr],d;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            d=dis[fr]+edges[i].l;
            if(d<dis[to]) dis[to]=d,q.push(pii(to,d));
        }
    }
}

int main()
{
    int v,e;
    scanf("%d %d",&v,&e);
    G.init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G.add(fr,to,l);
    }
    G.Dij(1);
    printf("%d\n",dis[v]);
    return 0;
}

/*=======================================
added at 2019.Apr10 15:10:22	problem:POJ3159
差分约束系统
=======================================*/