#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXV=1505,MAXE=MAXV*MAXV;
const int INF=0x7f7f7f7f;
int dp[MAXV];
int v,e;

struct Graph
{
    int top,head[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
};
Graph G;

struct Graph1:Graph
{
    int in[MAXV];
    void topsort()
    {
        memset(dp,0,sizeof(dp));
        queue<int> q;
        for(int i=1;i<=v;++i)
            if(!in[i]) q.push(i);
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int i=head[fr];i!=-1;i=edges[i].last)
            {
                to=edges[i].to;
                dp[to]=max(dp[to],dp[fr]+edges[i].l);
                if(!(--in[to])) q.push(to);
            }
        }
    }
};
Graph1 G2;

int dis[4][MAXV];
bool vis[MAXV];
struct cmp
{
    bool operator()(pii a,pii b) { return a.second>b.second; }
};
int Dij(int start,int end,int* dis)
{
    fill(dis+1,dis+v+1,INF);
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
        for(int i=G.head[fr],newd;i!=-1;i=G.edges[i].last)
        {
            to=G.edges[i].to;
            if(vis[to]) continue;
            newd=dis[fr]+G.edges[i].l;
            if(newd<dis[to]) dis[to]=newd,q.push(pii(to,newd));
        }
    }
    return dis[end];
}

int main()
{
    scanf("%d %d",&v,&e);
    int s1,e1,s2,e2;
    scanf("%d%d%d%d",&s1,&e1,&s2,&e2);
    G.init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G.add(fr,to,l),G.add(to,fr,l);
    }
    Dij(s1,e1,dis[0]),Dij(e1,s1,dis[1]);
    Dij(s2,e2,dis[2]),Dij(e2,s2,dis[3]);
    G2.init();
    memset(G2.in,0,sizeof(G2.in));
    for(int fr=1,to,l;fr<=v;++fr)
    {
        for(int i=G.head[fr];i!=-1;i=G.edges[i].last)
        {
            to=G.edges[i].to,l=G.edges[i].l;
            if(dis[0][fr]+l+dis[1][to]==dis[0][e1]&&dis[2][fr]+l+dis[3][to]==dis[2][e2])
                G2.add(fr,to,l),++G2.in[to];
        }
    }
    G2.topsort();
    int ans=0;
    for(int i=1;i<=v;++i)
        if(dp[i]>ans) ans=dp[i];
    G2.init();
    memset(G2.in,0,sizeof(G2.in));
    for(int fr=1,to,l;fr<=v;++fr)
    {
        for(int i=G.head[fr];i!=-1;i=G.edges[i].last)
        {
            to=G.edges[i].to,l=G.edges[i].l;
            if(dis[0][fr]+l+dis[1][to]==dis[0][e1]&&dis[3][fr]+l+dis[2][to]==dis[2][e2])
                G2.add(to,fr,l),++G2.in[fr];
        }
    }
    G2.topsort();
    for(int i=1;i<=v;++i)
        if(dp[i]>ans) ans=dp[i];
    printf("%d\n",ans);
    return 0;
}

/*=======================================
added at 2019.Apr03 22:16:36	problem:BZOJ1880
8 8  1 3 2 4  1 6 1  3 8 1  2 5 1  4 7 1  5 6 1  6 7 1  7 8 1  8 5 1(1)
4 4  1 4 2 3  1 2 10  1 3 1  4 2 9  4 3 2(2)
5 5  1 5 2 4  1 5 10  1 2 3  2 3 5  3 4 1  4 5 2
最短路+DAG拓扑排序找最长路
此题告诉我们不要用template~
=======================================*/