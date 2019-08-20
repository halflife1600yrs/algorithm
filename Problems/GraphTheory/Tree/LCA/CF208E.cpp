#pragma GCC optimize ("O2")
#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=MAXV,DEP=18,INF=0x7f7f7f7f;
int v,q;
vector<int> layer[MAXV];

namespace G
{
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } es[MAXE];
    
    int head[MAXV],top;

    void init() { top=0,memset(head,-1,sizeof(head)); }

    void add(int fr,int to)
    {
        es[top].set(to,head[fr]);
        head[fr]=top++;
    }

    int dis[MAXV],dfn[MAXV],pos[MAXV],dfs_num;
    int fa[MAXV][DEP];

    void dfs(int fr,int d)
    {
        dis[fr]=d,dfn[fr]=++dfs_num;
        pos[fr]=layer[d].size();
        layer[d].push_back(dfs_num);
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            fa[to][0]=fr;
            dfs(to,d+1);
        }
    }

    void build()
    {
        dfs_num=0;
        for(int i=1;i<=v;++i)
            if(!dfn[i]) dfs(i,0);
        for(int i=1;i<=v;++i)
            for(int j=1,k=fa[i][0];(1<<j)<=dis[i];++j)
                k=(fa[i][j]=fa[k][j-1]);
    }

    int query(int k,int p)
    {
        int d=dis[k];
        if(p>d) return 1;
        for(int i=0;(1<<i)<=p;++i)
            if((1<<i)&p)
                k=fa[k][i];
        int nxt=(pos[k]==layer[dis[k]].size()-1)?INF:layer[dis[k]][pos[k]+1];
        return upper_bound(layer[d].begin(),layer[d].end(),nxt)
            -upper_bound(layer[d].begin(),layer[d].end(),dfn[k]);
    }
}

int main()
{
    scanf("%d",&v);
    G::init();
    for(int i=1,fa;i<=v;++i)
    {
        scanf("%d",&fa);
        if(fa) G::add(fa,i);
    }
    G::build();
    scanf("%d",&q);
    int k,p,ans;
    char c=' ';
    for(int qq=0;qq<q;++qq)
    {
        if(q==qq-1) c='\n';
        scanf("%d %d",&k,&p);
        ans=G::query(k,p);
        if(ans<0) printf("0%c",c);
        else printf("%d%c",ans-1,c);
    }
    return 0;
}

/*==================================================================
added at 2019-08-15 14:10:42 暑假校选1C
利用lca然后dfs序以及保存每层的节点实现log查询每个节点的k层子节点
十分巧妙
比赛的时候想的错误方法是用倍增的思路保存父节点的二次幂层子节点的最左边和最右边
这是有问题的容易出现找不到目标层的情况
==================================================================*/