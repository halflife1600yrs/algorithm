#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=1e4+5;
int dp[MAXN][3],maxi[MAXN],ans[MAXN]; // dp[0]向下最大距离,dp[1]次大,dp[2]向上最大
namespace T
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXN<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    bool vis[MAXN];
    int dfs1(int fa)
    {
        vis[fa]=1;
        int to;
        for(int i=head[fa],l1,l2;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            dfs1(to);
            l1=dp[to][0]+edges[i].l,l2=dp[to][1]+edges[i].l;
            if(l1>dp[fa][0])
            { // 更新最大值
                dp[fa][1]=dp[fa][0];
                dp[fa][0]=l1;
                maxi[fa]=to;
            } else if(l1>dp[fa][1])
            { // 更新次大值
                dp[fa][1]=l1;
            }
        }
    }
    void dfs2(int fa)
    {
        vis[fa]=1;
        int to;
        for(int i=head[fa];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            dp[to][2]=dp[fa][2]+edges[i].l;
            if(to!=maxi[fa]) dp[to][2]=max(dp[to][2],dp[fa][0]+edges[i].l);
            else if(dp[fa][1]) // 有次大距离的话
                dp[to][2]=max(dp[to][2],dp[fa][1]+edges[i].l);
            ans[to]=max(dp[to][0],dp[to][2]);
            dfs2(to);
        }
    }
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        T::init();
        for(int i=2,to,v;i<=n;++i)
        {
            scanf("%d%d",&to,&v);
            T::add(i,to,v),T::add(to,i,v);
        }
        memset(dp,0,sizeof(dp));
        memset(T::vis,0,sizeof(T::vis));
        T::dfs1(1);
        memset(T::vis,0,sizeof(T::vis));
        dp[1][2]=0;
        ans[1]=dp[1][0];
        T::dfs2(1);
        for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-10 10:33:52 HDU2196
5
1 4
1 3
2 13
3 5

17
13
20
25
25

7
1 2
1 3
2 2
2 1
3 3
3 1
树形dp经典题,通过两次dfs计算树上每个节点对子树和它的父节点的贡献
需要保存最佳和次佳值,更新次佳值时应当判断最佳值的子节点和当前子节点是否相同
==================================================================*/