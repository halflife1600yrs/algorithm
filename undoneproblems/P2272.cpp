#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1e5+5,MAXE=1e6+5;
int mode,v,e;
ll ans,kind;

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

    int dfn[MAXV],low[MAXV],sz[MAXV],dfs_num;
    bool ins[MAXV];

    void dfs(int fr)
    {
        dfn[fr]=low[fr]=++dfs_num;
        ins[fr]=1,S::push(fr);
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
        if(dfn[fr]==low[fr])
        {
            sz[fr]=1;
            while(S::top()!=fr)
            {
                ++sz[fr];
                low[S::top()]=dfn[fr];
                ins[S::top()]=0;
                --S::t;
            }
            --S::t;
        }
    }

    void tarjan()
    {
        dfs_num=0;
        for(int i=1;i<=v;++i)
            if(!dfn[i]) dfs(i);
    }

    int head2[MAXV],in[MAXV];

    void shrink()
    {
        tarjan();
        memset(head2,-1,sizeof(head2));
        // memset(in,0,sizeof(in));
        for(int fr=1,to;fr<=v;++fr)
            for(int i=head[fr],j;~i&&(j=edges[i].last,1);i=j)
                if(low[fr]!=low[to=edges[i].to])
                {
                    ++in[to];
                    edges[i].set(low[to],head2[low[fr]]);
                    head2[low[fr]]=i;
                }
        for(int i=1;i<=v;++i) head[i]=head2[i];
    }

    ll dp[2][MAXV];

    void topo()
    {
        queue<int> q;
        for(int i=1;i<=v;++i)
            if(!in[i]) q.push(i),dp[1][i]=1;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            dp[0][fr]+=sz[fr];
            if(dp[0][fr]>ans) ans=dp[0][fr],kind=dp[1][fr];
            else if(dp[0][fr]>=ans) kind+=dp[1][fr];
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(dp[0][fr]>dp[0][to]) dp[0][to]=dp[0][fr],dp[1][to]=dp[1][fr];
                else if(dp[0][fr]==dp[0][to]) (dp[1][to]*=dp[1][fr])%=mode;
                if(!(--in[to])) q.push(to);
            }
        }
    }
}

int main()
{
    scanf("%d %d %d",&v,&e,&mode);
    int fr,to;
    G::init();
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        G::add(fr,to);
    }
    G::shrink();
    G::topo();
    printf("%d\n%d\n",ans,kind);
    return 0;
}