#include <bits/stdc++.h>

using namespace std;

const int MAXN=6005;
int val[MAXN],dp[MAXN][2];
namespace T
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } edges[MAXN];
    bool vis[MAXN];
    void init() { top=0,memset(head,-1,sizeof(head)),memset(vis,0,sizeof(vis)); }
    void add(int fr,int to)
    {
        edges[top].set(to,head[fr]);
        head[fr]=top++;
        vis[to]=1; // 标记所有不能作为树根的节点
    }
    void dfs(int fa)
    {
        int to;
        for(int i=head[fa];~i;i=edges[i].last)
        {
            to=edges[i].to;
            dfs(to);
            dp[fa][0]+=max(dp[to][0],dp[to][1]);
            dp[fa][1]+=dp[to][0];
        }
        dp[fa][1]+=val[fa];
    }
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        T::init();
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i) scanf("%d",&val[i]);
        int s,f;
        while(scanf("%d%d",&s,&f),(f+s)) T::add(f,s);
        int ans=0;
        for(int i=1;i<=n;++i)
        {
            if(!T::vis[i])
            {
                T::dfs(i);
                ans+=max(dp[i][0],dp[i][1]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-09 20:57:47 HDU1520
简单树形dp
题目比较坑没说有多组case
==================================================================*/