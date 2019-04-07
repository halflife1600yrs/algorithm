#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV=10000,MAXE=10000;
int v,e1,e2;

struct Graph
{
    int top,head[MAXV];
    int dis[MAXV],cnt[MAXV];
    bool vis[MAXV];
    struct Edge
    {
        int to,l,last;
        void set(int _to,int _l,int _last) { to=_to,l=_l,last=_last; }
    } edges[MAXE<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,l,head[fr]);
        head[fr]=top++;
    }
    bool spfa()
    {
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(cnt,0,sizeof(cnt));
        queue<int> q;
        dis[1]=0;
        q.push(1);
        vis[1]=cnt[1]=1;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            vis[fr]=0;
            for(int i=head[fr],newd;i!=-1;i=edges[i].last)
            {
                to=edges[i].to;
                newd=dis[fr]+edges[i].l;
                if(newd<dis[to])
                {
                    dis[to]=newd;
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
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&v,&e1,&e2);
        G.init();
        for(int i=0,fr,to,l;i<e1;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G.add(fr,to,l),G.add(to,fr,l);
        }
        for(int i=0,fr,to,l;i<e2;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G.add(fr,to,-l);
        }
        if(G.spfa()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*=======================================
added at 2019.Apr06 21:53:02	problem:POJ3259
spfa需要先更新值再判断是否在队列中
判负环模板题
=======================================*/