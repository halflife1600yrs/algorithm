#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=100;
int dp[2*MAXN][MAXN][MAXN];
int land[MAXN][MAXN];

inline void get_val(int l,int i,int j,int x,int y)
{
    dp[l][i][j]=max(dp[l][i][j],x!=y?(dp[l-1][x][y]+land[i][l-i+1]+land[j][l-j+1]):0);
    // printf("%d %d %d\n",i,j,x!=y?(dp[l-1][x][y]+land[i][l-i+1]+land[j][l-j+1]):0);
}

int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int n,m;
    scanf("%d %d",&n,&m);
    // debug2(n,m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&land[i][j]);
        }
    }
    dp[1][1][1]=0;
    for(int l=2;l<n+m;++l)
    {
        // debug1(l);
        for(int i=1;i<=n&&i<=l;++i)
        {
            for(int j=1;j<=n&&j<=l;++j)
            {
                get_val(l,i,j,i-1,j);
                get_val(l,i,j,i-1,j-1);
                get_val(l,i,j,i,j);
                get_val(l,i,j,i,j-1);
                // printf("%d ",dp[l][i][j]);
            }
            // printf("\n");
        }
        // printf("\n");
    }
    printf("%d\n",dp[n+m-1][n][n]);
    return 0;
}

/*==================================================================
added at 2019-07-08 19:36:39 P1006
这里一定要注意即使是矩形最大也是dp[l][n][n]
==================================================================*/