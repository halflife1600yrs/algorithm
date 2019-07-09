#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=20;
int dp[MAXN][MAXN][MAXN];
int land[MAXN][MAXN];

inline void get_val(int l,int i,int j,int x,int y)
{
    dp[l][i][j]=max(dp[l][i][j],dp[l-1][x][y]+land[i][l-i+1]+(i!=j?land[j][l-j+1]:0));
}

int main()
{
    int n;
    scanf("%d",&n);
    int x,y,v;
    while(scanf("%d %d %d",&x,&y,&v),(x+y+v)) land[x][y]=v;
    dp[1][1][1]=land[1][1];
    for(int l=2;l<2*n;++l)
    {
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
    printf("%d\n",dp[2*n-1][n][n]);
    return 0;
}