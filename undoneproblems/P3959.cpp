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

int graph[12][12],dis[12];
int dp[1<<12];
int n,m;

void add(int a,int b,int c)
{
    if(graph[a][b]<0||graph[a][b]>c) graph[a][b]=graph[b][a]=c;
}

void dfs(int state)
{
    debug1(state);
    for(int i=0;i<n;++i)
    {
        // debug2(i,dis[i]);
        if(state&(1<<i))
        {
            for(int j=0,ans,newState;j<n;++j)
            {
                if(!(state&(1<<j))&&graph[i][j]>0)
                {
                    // debug1(j);
                    ans=dp[state]+graph[i][j]*dis[i],newState=state|(1<<j);
                    if(dp[newState]<0||dp[newState]>ans)
                    {
                        dp[newState]=ans;
                        debug2(newState,dp[newState]);
                        int tmp=dis[j];
                        dis[j]=dis[i]+1;
                        dfs(newState);
                        dis[j]=tmp;
                    }
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    memset(graph,-1,sizeof(graph));
    for(int i=0,a,b,c;i<m;++i)
    {
        scanf("%d %d %d",&a,&b,&c);
        add(a-1,b-1,c);
    }
    int ans=0x7fffffff;
    for(int i=0;i<n;++i)
    {
        memset(dp,-1,sizeof(dp));
        memset(dis,-1,sizeof(dis));
        dis[i]=1;
        dfs(1<<i);
        if(dp[(1<<n)-1]<ans) ans=dp[(1<<n)-1];
    }
    printf("%d\n",ans);
    return 0;
}