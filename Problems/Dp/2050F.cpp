#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e3+5;
ll dp[MAXN][MAXN];

// 限制，体力累加值，做完之后
int main()
{
    int T;
    ll n,h0;
    scanf("%d",&T);
    for(int _=0;_<T;++_)
    {
        scanf("%lld %lld",&n,&h0);
        ll a,b,c;
        int ans=0;
        if(_) memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
        {
            scanf("%lld %lld %lld",&a,&b,&c);
            if(i==1)
            {
                dp[1][0]=h0+c;
                if(min(h0,b)-a>0) dp[1][1]=min(h0,b)-a+c;
                else dp[1][1]=0;
                continue;
            }
            for(int j=0;j<=i;++j)
            {
                dp[i][j]=0;
                if(dp[i-1][j]) dp[i][j]=dp[i-1][j]+c;
                if(min(dp[i-1][j-1],b)-a>0)
                    dp[i][j]=max(dp[i][j],min(dp[i-1][j-1],b)-a+c);
                if(!dp[i][j]) break;
                if(i==n&&dp[i][j]) ans=j;
            }
        }
        // debug1(dp[n][ans]);
        printf("%d\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr16 13:59:43	problem:2050F
dp
=======================================*/