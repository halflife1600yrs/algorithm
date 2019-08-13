#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1e5+5,MAXE=MAXV*2;
int v;

namespace T
{
    int head[MAXV],top;
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } es[MAXE];

    void init() { top=0,memset(head,-1,sizeof(head)); }

    void add(int fr,int to)
    {
        es[top].set(to,head[fr]);
        head[fr]=top++;
    }

    int vis[MAXV],sz[MAXV],time,SZ[5]; // 记录子树节点数以及所有节点距子树根节点距离之和
    ll dis[MAXV],ans[5],mini[5]; // 记录每个点到子树其他点的距离，每棵树的内部两两之和，dis的最小值

    void dfs1(int fr)
    {
        vis[fr]=time;
        sz[fr]=1,dis[fr]=0;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]) continue;
            dfs1(to);
            sz[fr]+=sz[to];
            dis[fr]+=dis[to]+sz[to];
        }
    }

    void dfs2(int fr,int fa)
    {
        mini[time]=min(mini[time],dis[fr]);
        ans[time]+=dis[fr];
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa) continue;
            dis[to]=dis[fr]+SZ[time]-2*sz[to];
            dfs2(to,fr);
        }
    }

    ll work()
    {
        time=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=v;++i)
        {
            if(!vis[i])
            {
                ++time;
                dfs1(i);
                mini[time]=0x7f7f7f7f,ans[time]=0;
                SZ[time]=sz[i];
                dfs2(i,-1);
            }
        }
        return mini[1]*SZ[2]+mini[2]*SZ[1]+SZ[1]*SZ[2]+ans[1]/2+ans[2]/2;
    }
}

int main()
{
    int fr,to;
    while(~scanf("%d",&v))
    {
        T::init();
        for(int i=1;i<v-1;++i)
        {
            scanf("%d %d",&fr,&to);
            T::add(fr,to);
            T::add(to,fr);
        }
        printf("%lld\n",T::work());
    }
    return 0;
}

/*==================================================================
added at 2019-08-11 19:30:54 CCPC2019江西省赛A
树形dp,求树上每个点到所有其他点的距离之和
==================================================================*/