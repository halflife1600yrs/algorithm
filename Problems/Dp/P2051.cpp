#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=9999973;
ll dp[105][105][105];
//dp[i][j][k]表示在i第i层，前面有j列1个1，k列2个1

inline int Cx2(int x) { return x*(x-1)/2; }

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    dp[0][0][0]=1;
    dp[0][1][0]=n;
    dp[0][2][0]=Cx2(n);
    for(int i=0;i<m-1;++i)
    {
        for(int j=0;j<=n;++j)
        {
            for(int k=0;k<=n-j;++k)
            {
                dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%MODE;
                if(j) dp[i+1][j-1][k+1]=(dp[i+1][j-1][k+1]+dp[i][j][k]*j)%MODE;
                if(n-j-k) dp[i+1][j+1][k]=(dp[i+1][j+1][k]+dp[i][j][k]*(n-j-k))%MODE;
                if(n-j-k>1) dp[i+1][j+2][k]=(dp[i+1][j+2][k]+dp[i][j][k]*Cx2(n-j-k))%MODE;
                if(n-j-k&&j) dp[i+1][j][k+1]=(dp[i+1][j][k+1]+dp[i][j][k]*(n-j-k)*(j))%MODE;
                if(j>1) dp[i+1][j-2][k+2]=(dp[i+1][j-2][k+2]+dp[i][j][k]*Cx2(j))%MODE;
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n-i;++j)
            ans=(ans+dp[m-1][i][j])%MODE;
    printf("%lld\n",ans);
    return 0;
}

/*=======================================
added at 2019.Mar09 16:57:31	problem:P2051
类似于状压dp，但是状态转移只根据每个状态的数目而不是具体位置
因此可以枚举每种状态的具体数目
=======================================*/