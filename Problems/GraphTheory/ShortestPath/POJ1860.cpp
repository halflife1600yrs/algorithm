#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int MAXV=2000,MAXE=2000;

struct Graph
{
    int top,head[MAXV],cnt[MAXV];
    bool vis[MAXV];
    double dis[MAXV];
    struct Edge
    {
        int to,last;
        double v1,v2;
        void set(int _to,int _last,double _v1,double _v2) { to=_to,last=_last,v1=_v1,v2=_v2; }
    } edges[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,double v1,double v2)
    {
        edges[top].set(to,head[fr],v1,v2);
        head[fr]=top++;
    }
    bool spfa(int start,int v,double origin)
    {
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        memset(cnt,0,sizeof(cnt));
        queue<int> q;
        dis[start]=origin;
        q.push(start);
        vis[start]=cnt[start]=1;
        int fr,to;
        double d;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            vis[fr]=0;
            for(int i=head[fr];i!=-1;i=edges[i].last)
            {
                to=edges[i].to;
                d=(dis[fr]-edges[i].v2)*edges[i].v1;
                if(d>dis[to])
                {
                    dis[to]=d;
                    if(vis[to]) continue;
                    vis[to]=1,++cnt[to];
                    if(cnt[to]>v) return 1;
                    q.push(to);
                }
            }
        }
        return 0;
    }
} G;

int main()
{
    int v,e,start;
    double origin;
    while(~scanf("%d %d %d %lf",&v,&e,&start,&origin))
    {
        G.init();
        double r1,c1,r2,c2;
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d %lf %lf %lf %lf",&fr,&to,&r1,&c1,&r2,&c2);
            G.add(fr,to,r1,c1),G.add(to,fr,r2,c2);
        }
        if(G.spfa(start,v,origin)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*=======================================
added at 2019.Apr08 21:08:55	problem:POJ1068
double写成int了
=======================================*/