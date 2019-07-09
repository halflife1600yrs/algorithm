#include <bits/stdc++.h>

using namespace std;

const int MAXN=550,MODE=1000000007;
typedef long long ll;
char land[MAXN][MAXN];
ll dp[2][MAXN][MAXN];

int main()
{
    // freopen(".in","r",stdin);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%s",land[i]);
    if(land[0][0]==land[n-1][n-1]) dp[0][0][0]=1;
    else
    {
        printf("0\n");
        return 0;
    }
    bool pos=1;
    for(int l=1;l<n;++l)
    {
        for(int i=0;i<=l;++i)
        {
            for(int j=0;j<=l;++j)
            {
                dp[pos][i][j]=0;
                if(land[i][l-i]==land[n-1-j][n-1-l+j])
                {
                    dp[pos][i][j]=dp[!pos][i-1][j]+dp[!pos][i][j]+dp[!pos][i-1][j-1]+dp[!pos][i][j-1];
                    if(dp[pos][i][j]>=MODE) dp[pos][i][j]%=MODE;
                }
            }
        }
        pos=!pos;
    }
    ll ans=0;
    for(int i=0;i<n;++i)
    {
        ans+=dp[!pos][i][n-1-i];
        if(ans>=MODE) ans%=MODE;
    }
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-07-09 16:53:29 P3126
dp公式中下标出现-1
开大数组后解决,但是以后dp的时候数组尽量从1开始放
==================================================================*/