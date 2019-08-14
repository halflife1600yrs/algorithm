#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=MAXV,INF=0x7f7f7f7f;
int v,e,ans[MAXV];

namespace S
{
    int data[MAXV],t;
    void push(int x) { data[t++]=x; }
    int top() { return data[t-1]; }
}

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int dfn[MAXV],low[MAXV],dfs_num,sz[MAXV];
    bool ins[MAXV];

    void dfs(int fr)
    {
        dfn[fr]=low[fr]=++dfs_num;
        ins[fr]=1;
        S::push(fr);
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(!dfn[to])
            {
                dfs(to);
                low[fr]=min(low[fr],low[to]);
            } else if(ins[to])
                low[fr]=min(low[fr],low[to]);
        }
        if(low[fr]==dfn[fr])
        {
            sz[dfn[fr]]=1;
            while(S::top()!=fr)
            {
                low[S::top()]=dfn[fr];
                ins[S::top()]=0;
                ++sz[dfn[fr]];
                --S::t;
            }
            ins[fr]=0;
            --S::t;
        }
    }

    void tarjan()
    {
        dfs_num=0;
        for(int i=1;i<=v;++i)
            if(!dfn[i]) dfs(i);
    }

    int in[MAXV];

    void work()
    {
        tarjan();
        for(int i=1;i<=v;++i)
            for(int j=head[i];~j;j=edges[j].last)
                if(low[i]!=low[edges[j].to])
                    ++in[low[edges[j].to]];
        memset(ans,0x7f,sizeof(ans));
        for(int i=1;i<=v;++i)
            if(!in[low[i]])
                ans[low[i]]=min(ans[low[i]],i);
    }
}

int main()
{
    scanf("%d %d",&v,&e);
    int fr,to;
    G::init();
    for(int i=0;i<e;++i)    
    {
        scanf("%d %d",&fr,&to);
        G::add(fr,to);
    }
    G::work();
    sort(ans+1,ans+v+1);
    printf("%d\n",lower_bound(ans+1,ans+v+1,INF)-ans-1);
    int i=1;
    while(ans[i+1]!=INF) printf("%d ",ans[i++]);
    printf("%d\n",ans[i]);
    return 0;
}

/*==================================================================
added at 2019-08-14 09:48:17 NK15707
缩点之后每个强连通分量中应该取一个点作为代表
==================================================================*/