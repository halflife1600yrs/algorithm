#include <bits/stdc++.h>

using namespace std;

const int MAXN=205;
int dp[MAXN][10];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    dp[1][1]=1;
    for(int i=2;i<=n;++i)
        for(int j=1;j<=k&&j<=i;++j)
            dp[i][j]=dp[i-1][j-1]+dp[i-j][j];
    printf("%d\n",dp[n][k]);
    return 0;
}