#include <bits/stdc++.h>

using namespace std;

#define ll int
const int MAXV=1e4+5,MAXE=1e5+5;
int v,e;
ll val[MAXV],sum[MAXV];

struct Graph
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
};

struct Toposort : Graph
{
    int in[MAXV];
    ll dp[MAXV];

    void add(int fr, int to) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }

    ll toposort()
    {
        queue<int> q;
        // memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= v; ++i)
            if(!in[i]) q.push(i);
        ll ans=0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            dp[fr]+=sum[fr];
            if(dp[fr]>ans) ans=dp[fr];
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                dp[to] = max(dp[to], dp[fr]);
                if(!(--in[to])) q.push(to);
            }
        }
        return ans;
    }
} G2;

namespace S
{
    int  data[MAXV],t;
    inline void push(int x) { data[t++]=x; }
    inline int top() { return data[t-1]; }
}

struct Tarjan : Graph
{
    int dfn[MAXV],low[MAXV],dfs_num;
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
        if(dfn[fr]==low[fr])
        {
            sum[dfn[fr]]=val[fr];
            while(S::top()!=fr)
            {
                low[S::top()]=dfn[fr];
                ins[S::top()]=0;
                sum[dfn[fr]]+=val[S::top()];
                --S::t;
            }
            ins[fr]=0;
            --S::t;
        }
    }

    void tarjan()
    {
        // memset(dfn,0,sizeof(dfn));
        // memset(ins,0,sizeof(ins));
        dfs_num=0;
        for(int i=1;i<=v;++i)
            if(!dfn[i]) dfs(i);
    }

    void shrink()
    {
        tarjan();
        for(int i=1;i<=v;++i)
            for(int j=head[i];~j;j=edges[j].last)
                if(low[i]!=low[edges[j].to])
                    G2.add(low[i],low[edges[j].to]);
    }
} G1;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d %d",&v,&e);
    G1.init(),G2.init();
    for(int i=1;i<=v;++i) scanf("%d",&val[i]);
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        G1.add(fr,to);
    }
    G1.shrink();
    printf("%lld\n",G2.toposort());
    return 0;
}

/*=======================================
added at 2019.May26 11:48:39	problem:P3387
tarjan缩点模板题
需要注意的就是缩点后每个点的信息要保存在一个新数组中
还要出栈时统一修改并查集的father
=======================================*/