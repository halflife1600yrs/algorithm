#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=2e5+5,MODE=998244353;
int dp[MAXN][450];

inline int limit(int x)
{
    return floor(sqrt(x));
}

int main()
{
    int T,n;
    dp[1][1]=1;
    for(int i=2;i<MAXN;++i)
        for(int j=i&1?1:2,end=limit(i);j<=end;j+=2)
            dp[i][j]=(1ll*dp[i-2*j+1][j-1]+dp[i-2*j][j])%MODE;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll ans=0;
        for(int i=n&1?1:2,end=limit(n);i<=end;i+=2)
        {
            ans+=dp[n][i];
            if(ans>=MODE) ans%=MODE;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr25 20:19:58	problem:CSU2310
整数划分问题
=======================================*/