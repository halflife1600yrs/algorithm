#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e6+5,MAXE=MAXV<<1;
int v,val[MAXV],dp[MAXV][2];

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE]; 

    int top, head[MAXV],uset[MAXV];

    int get_fa(int x)
    {
        if(uset[x]==x) return x;
        return uset[x]=get_fa(uset[x]);
    }

    void init()
    {
        top = 0, memset(head, -1, sizeof(head));
        for(int i=0;i<v;++i) uset[i]=i;
    }

    bool add(int fr, int to)
    {
        int x=get_fa(fr),y=get_fa(to);
        if(x==y) return 1;
        es[top].set(to, head[fr]);
        head[fr] = top++;
        es[top].set(fr,head[to]);
        head[to]=top++;
        uset[x]=y;
        return 0;
    }

    void dfs(int fr,int fa)
    {
        dp[fr][0]=0,dp[fr][1]=val[fr];
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa) continue;
            dfs(to,fr);
            dp[fr][0]+=max(dp[to][1],dp[to][0]);
            dp[fr][1]+=dp[to][0];
        }
    }
}

int main()
{
    scanf("%d",&v);
    for(int i=0;i<v;++i) scanf("%d",&val[i]);
    G::init();
    int p1,p2,vv1,vv2;
    for(int i=0,fr,to;i<v;++i)
    {
        scanf("%d %d",&fr,&to);
        if(G::add(fr,to)) p1=fr,vv1=val[fr],p2=to,vv2=val[to];
    }
    val[p2]=0;
    G::dfs(p1,-1);
    int ans=max(dp[p1][0],dp[p1][1]);
    val[p2]=vv2,val[p1]=0;
    G::dfs(p2,-1);
    ans=max(ans,max(dp[p2][0],dp[p2][1]));
    double k;
    scanf("%lf",&k);
    printf("%.1lf\n",k*ans);
    return 0;
}

/*==================================================================
added at 2019-07-26 21:10:51 P1453
基环树第一题
思路很简单,删一条边断环,对两个点分别dfs一次,强制另一个点不取,选大的就行
==================================================================*/