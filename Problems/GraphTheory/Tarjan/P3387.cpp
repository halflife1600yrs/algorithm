#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXV=1e5+5,MAXE=1e6+5;
int v,e,mode;
int ans,kind;

inline int plu(int x,int y)
{
    return (x+=y)>=mode?x%mode:x;
}

namespace S
{
    int  data[MAXV],t;
    inline void push(int x) { data[t++]=x; }
    inline int top() { return data[t-1]; }
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
        ins[fr]=1,S::push(fr);
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(!dfn[to])
            {
                dfs(to);
                low[fr]=min(low[fr],low[to]);
            } else if(ins[to])
                low[fr]=min(low[fr],dfn[to]);
        }
        if(dfn[fr]==low[fr])
        {
            sz[dfn[fr]]=1;
            while(S::top()!=fr)
            {
                ++sz[dfn[fr]];
                low[S::top()]=dfn[fr];
                ins[S::top()]=0;
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
        dfs_num=S::t=0;
        for(int i=1;i<=v;++i)
            if(!dfn[i]) dfs(i);
    }

    int times[MAXV],head2[MAXV],in[MAXV];

    void shrink()
    {
        tarjan();
        fill(head2+1,head2+1+v,-1);
        // fill(in+1,in+1+v,0);
        for(int fr=1,i,j;fr<=v;++fr)
            for(i=head[fr];~i&&(j=edges[i].last,1);i=j)
                if(low[edges[i].to]!=low[fr])
                {
                    edges[i].set(low[edges[i].to],head2[low[fr]]);
                    head2[low[fr]]=i;
                }
        // fill(times+1,times+1+v,0);
        for(int fr=1,to,i,j;fr<=v;++fr)
            for(head[fr]=-1,i=head2[fr];~i&&(j=edges[i].last,1);i=j)
                if(times[to=edges[i].to]!=fr)
                {
                    times[to]=fr;
                    edges[i].set(to,head[fr]);
                    head[fr]=i;
                    ++in[to];
                }
    }

    int dp[2][MAXV]; // 记录点数/方法数

    void toposort()
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
            else if(dp[0][fr]==ans) kind=plu(kind,dp[1][fr]);
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(dp[0][fr]>dp[0][to]) dp[0][to]=dp[0][fr],dp[1][to]=dp[1][fr];
                else if(dp[0][fr]==dp[0][to]) dp[1][to]=plu(dp[1][to],dp[1][fr]);
                if(!(--in[to])) q.push(to);
            }
        }
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d %d %d",&v,&e,&mode);
    G::init();
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        G::add(fr,to);
    }
    G::shrink();
    G::toposort();
    printf("%d\n%d\n",ans,kind%mode);
    return 0;
}

/*=======================================
added at 2019.May26 11:48:39	problem:P3387
tarjan缩点模板题
需要注意的就是缩点后每个点的信息要保存在一个新数组中
还要出栈时统一修改并查集的father
=======================================*/

/*==================================================================
added at 2019-08-20 21:40:29 P3387
更新了缩点的写法
==================================================================*/