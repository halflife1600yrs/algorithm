#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1e5+5,MAXE=MAXV<<1;
int v,mode,dp[MAXV][2]; // 从根节点开始dfs,表示这个点等于dp[i][0]+dp[i][1]*root(mod p)

ll inv(ll x)
{
    ll ans=1;
    int up=mode-2;
    while(up)
    {
        if(up&1) ans=ans*x%mode;
        x=x*x%mode;
        up>>=1;
    }
    return ans;
}

namespace G
{
    struct Edge
    {
        int to, last, a,b,c;
        void set(int _to, int _last,int _a,int _b,int _c) { to = _to, last = _last,a=_a,b=_b,c=_c; }
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

    bool add(int fr, int to,int a,int b,int c)
    {
        int x=get_fa(fr),y=get_fa(to);
        if(x==y) return 1;
        es[top].set(to, head[fr],a,b,c);
        head[fr] = top++;
        es[top].set(fr,head[to],b,a,c);
        head[to]=top++;
        uset[x]=y;
        return 0;
    }

    void dfs(int fr,int fa)
    {
        ll tmp;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa) continue;
            tmp=inv(es[i].b);
            dp[to][0]=tmp*((es[i].c-1ll*es[i].a*dp[fr][0])%mode)%mode;
            if(dp[to][0]<0) (dp[to][0]+=mode)%=mode;
            dp[to][1]=mode-tmp*es[i].a%mode*dp[fr][1]%mode;
            dfs(to,fr);
        }
    }
}

int main()
{
    scanf("%d %d",&v,&mode);
    int p1,p2;
    ll k1,k2,k3;
    G::init();
    for(int i=1,fr,to,a,b,c;i<=v;++i) 
    {
        scanf("%d %d %d %d %d",&fr,&to,&a,&b,&c);
        if(G::add(fr,to,a,b,c)) p1=fr,p2=to,k1=a,k2=b,k3=c;
    }
    dp[1][0]=0,dp[1][1]=1;
    G::dfs(1,-1);
    ll x=(k1*dp[p1][1]+k2*dp[p2][1])%mode,y=(k3-k1*dp[p1][0]-k2*dp[p2][0])%mode;
    if(y<0) (y+=mode)%=mode;
    ll ans=y*inv(x)%mode;
    for(int i=1;i<=v;++i)
        printf("%lld\n",(dp[i][0]+dp[i][1]*ans)%mode);
    return 0;
}

/*==================================================================
added at 2019-07-27 10:22:29 NK13334
基环树
每条边是一个二元线性同余方程,因此确定一个点就可以确定另一个点
用dfs求解这些线性方程,用a+bx表示每个点和root的关系
其中的环构成一个方程组,解这个方程就可以得到root的值,然后对每个点代进去
==================================================================*/