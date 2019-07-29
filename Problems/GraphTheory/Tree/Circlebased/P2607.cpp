#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=2e6+5,MAXE=MAXV<<1;

struct triad
{
    int p1,p2,val;
    triad(int _p1=0,int _p2=0,int _val=0)
    :p1(_p1),p2(_p2),val(_val) {}
} q[MAXV];
int qt=0;

int v,val[MAXV];
ll dp[MAXV][2];

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
        for(int i=1;i<=v;++i) uset[i]=i;
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

    ll work()
    {
        int p1,p2;
        ll ans=0,tmp;
        for(int i=0;i<qt;++i)
        {
            p1=q[i].p1,p2=q[i].p2;
            val[p2]=0;
            dfs(p1,-1);
            tmp=max(dp[p1][0],dp[p1][1]);
            val[p2]=q[i].val,val[p1]=0;
            dfs(p2,-1);
            ans+=max(tmp,max(dp[p2][0],dp[p2][1]));
        }
        return ans;
    }
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

int main()
{
    read(v);
    G::init();
    for(int i=1,to;i<=v;++i)
    {
        read(val[i]),read(to);
        if(G::add(i,to)) q[qt++]=triad(i,to,val[to]);
    }
    printf("%lld",G::work());
    return 0;
}

/*==================================================================
added at 2019-07-26 21:44:35 P2607
基环树森林,就记录每条环边即可
==================================================================*/