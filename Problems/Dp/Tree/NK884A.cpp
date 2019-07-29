#include <bits/stdc++.h>

using namespace std;
  
const int MAXN=1.5e5+5;
typedef vector<int>::iterator vit;
int dp[MAXN][3],maxi[MAXN],ans=0x7f7f7f7f; // dp[0]向下遇到人最大距离,dp[1]次大
int n,k,root;
bool have[MAXN];
bool vis[MAXN];
 
namespace S
{
    struct Node
    {
        int fr;
        vit i;
    } s[MAXN];
    int T=0;
    void add(int fr,vit i)
    {
        s[T].fr=fr;
        s[T].i=i;
        ++T;
    }
    void pop()
    {
        --T;
    }
}
 
namespace T
{
    vector<int> es[MAXN];
    void add(int fr,int to)
    {
        es[fr].push_back(to);
    }
 
    void change1(int fr,int to)
    {
        int l1=(dp[to][0]==-1?-1:dp[to][0]+1),l2=(dp[to][1]==-1?-1:dp[to][1]+1);
        if(l1>dp[fr][0])
        {
            dp[fr][1]=dp[fr][0];
            dp[fr][0]=l1;
            maxi[fr]=to;
        } else if(l1>dp[fr][1])
        {
            dp[fr][1]=l1;
        }
    }
    #define S_T (S::s[S::T-1])
    void dfs1()
    {
        // 初始化
        S::add(root,es[root].begin());
        vis[root]=1;
        if(have[root]) dp[root][0]=0;
        else dp[root][0]=-1;
        //
        while(S::T)
        {
            // 当前状态
            int& fr=S_T.fr;
            vit& i=S_T.i;
            // 判断终止条件
            if(i==es[fr].end())
            { // 返回
                S::pop();
                change1(S_T.fr,fr);
                continue;
            }
            // 该状态可行
            if(!vis[*i])
            {
                if(have[*i]) dp[*i][0]=0;
                else dp[*i][0]=-1;
                dp[*i][1]=-1;
                vis[*i]=1;
                S::add(*i,es[*i].begin());
            }
            // 转移当前状态
            ++i;
        }
    }
 
    void change2(int fr,int to)
    {
        if(dp[fr][2]!=-1) dp[to][2]=dp[fr][2]+1;
        else dp[to][2]=-1;
        if(to!=maxi[fr])
        {
            if(dp[fr][0]!=-1) dp[to][2]=max(dp[to][2],1+dp[fr][0]);
        } else if(dp[fr][1]!=-1) dp[to][2]=max(dp[to][2],1+dp[fr][1]);
        ans=min(ans,max(dp[fr][0],dp[fr][2]));
    }
 
    void dfs2()
    {
        // 初始化
        S::T=0;
        memset(vis,0,sizeof(vis));
        dp[root][2]=-1;
        S::add(root,es[root].begin());
        vis[root]=1;
        //
        while(S::T)
        {
            // 获取当前状态
            int& fr=S_T.fr;
            vit& i=S_T.i;
            // 判断终止条件
            if(i==es[fr].end())
            {
                S::pop();
                continue;
            }
            // 该状态可行
            if(!vis[*i])
            {
                change2(fr,*i);
                S::add(*i,es[*i].begin());
                vis[*i]=1;
            }
            // 转移当前状态
            ++i;
        }
    }
    #undef S_T
}
 
int main()
{
    scanf("%d %d",&n,&k);
    for(int i=1,fr,to;i<n;++i)
    {
        scanf("%d %d",&fr,&to);
        T::add(fr,to),T::add(to,fr);
    }
    for(int i=0,a;i<k;++i) scanf("%d",&a),have[a]=1;
    root=1;
    T::dfs1();
    T::dfs2();
    printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-07-27 21:24:00 NK884A
跟HDU2196差不多
可以直接用树的直径做
用了避免递归的方式写
==================================================================*/