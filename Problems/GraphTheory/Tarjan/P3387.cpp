#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e4+5,MAXE=1e5+5;
int v,e;
int val[MAXV],sz[MAXV],dp[MAXV];

struct Quee
{
    int data[MAXV],t;
    void add(int x) { data[t++]=x; }
    int top() { return data[t-1]; }
} S;

struct Graph
{ // 向前星存边框架,后面的算法继承此类;比赛的时候把struct去掉
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE*2];
    
    int top, head[MAXV];

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    void init() { top = 0,memset(head, -1, sizeof(head)); }
};

struct TopSort : Graph
{
    int in[MAXV], dp[MAXV];
    void add(int fr, int to) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }

    int topsort()
    {
        queue<int> q;
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= v; ++i)
            if(!in[i]) q.push(i);
        int fr, to, maxi, ans=0;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            if(dp[fr]+sz[fr]>ans) ans=dp[fr]+sz[fr];
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                dp[to]=max(dp[fr]+sz[fr],dp[to]);
                if(!(--in[to])) q.push(to);
            }
        }
        return ans;
    }
} G;

struct TARJAN : Graph
{

    bool ins[MAXV];
    int low[MAXV], dfn[MAXV], dfs_num;

    int tarjan()
    {
        dfs_num = S.t = 0;
        memset(ins, 0, sizeof(ins));
        memset(dfn, -1, sizeof(dfn));
        int ans = 0;
        for(int i = 1; i <= v; ++i)
            if(dfn[i] == -1) ans += dfs(i);
        return ans;
    }

    int dfs(int fr)
    {
        low[fr] = dfn[fr] = ++dfs_num;
        S.add(fr);
        ins[fr] = 1;
        int to, ans = 0;
        for(int i = head[fr]; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(dfn[to] == -1)
            {
                ans += dfs(to);
                low[fr] = min(low[to], low[fr]);
            } else if(ins[to])
                low[fr] = min(dfn[to], low[fr]);
        }
        if(dfn[fr] == low[fr])
        {
            ++ans;
            while(S.top()!=fr)
            {
                sz[dfn[fr]]+=val[S.top()];
                low[S.top()]=dfn[fr];
                ins[S.top()]=0;
                --S.t;
            }
            --S.t;
            ins[fr]=0;
            sz[dfn[fr]]+=val[fr];
        }
        
        return ans;
    }

    void shrink()
    {
        for(int i=1;i<=v;++i)
            for(int j=head[i],k;~j;j=edges[j].last)
            {
                k=edges[j].to;
                if(low[i]!=low[k]) G.add(low[i],low[k]);
            }
    }
} T;

int main()
{
    scanf("%d %d",&v,&e);
    for(int i=1;i<=v;++i)
        scanf("%d",&val[i]);
    T.init();
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        T.add(fr,to);
    }
    G.init();
    T.tarjan();
    T.shrink();
    printf("%d\n",G.topsort());
    return 0;
}

/*=======================================
added at 2019.May26 11:48:39	problem:P3387
tarjan缩点模板题
需要注意的就是缩点后每个点的信息要保存在一个新数组中
还要出栈时统一修改并查集的father
=======================================*/