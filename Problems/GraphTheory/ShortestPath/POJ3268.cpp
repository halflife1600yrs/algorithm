#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;
typedef pair<int,int> pii;
const int MAXV=2005,MAXE=2e5+5,INF=0x7f7f7f7f;
int v,e,center,dis[2][MAXV];
struct cmp
{
    bool operator()(pii a,pii b) { return a.second>b.second; }
};
struct Graph
{
    int edges[MAXV][MAXV];
    bool vis[MAXV];
    void init() { memset(edges,-1,sizeof(edges)); }
    void add(int fr,int to,int l)
    {
        edges[fr][to]=l;
    }
    void Dij(int start,int* pdis)
    {
        fill(pdis+1,pdis+v+1,INF);
        memset(vis,0,sizeof(vis));
        priority_queue<pii,vector<pii>,cmp> q;
        pdis[start]=0;
        q.push(pii(start,0));
        int fr,to;
        while(!q.empty())
        {
            fr=q.top().first,q.pop();
            if(vis[fr]) continue;
            vis[fr]=1;
            for(int to=1,newd;to<=v;++to)
            {
                if(vis[to]||to==fr||edges[fr][to]<0) continue;
                newd=pdis[fr]+edges[fr][to];
                if(newd<pdis[to]) pdis[to]=newd,q.push(pii(to,newd));
            }
        }
    }
} G;
int main()
{
    scanf("%d %d %d",&v,&e,&center);
    G.init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G.add(fr,to,l);
    }
    G.Dij(center,dis[0]);
    for(int i=1;i<v;++i)
        for(int j=i+1;j<=v;++j) swap(G.edges[i][j],G.edges[j][i]);
    G.Dij(center,dis[1]);
    int maxi=0;
    for(int i=1;i<=v;++i)
        if(i!=center&&dis[0][i]+dis[1][i]>maxi) maxi=dis[0][i]+dis[1][i];
    printf("%d\n",maxi);
    return 0;
}

/*=======================================
added at 2019.Apr09 21:18:14	problem:POJ3268
汇点的来最短路+去最短路
对图进行转置
=======================================*/