#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll dp[2][1024][100];
int I[1024];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0;i<(1<<n);++i)
        for(int j=0;j<10;++j)
            if(i&(1<<j)) ++I[i];
    bool pos=0;
    dp[1][0][0]=1;
    for(int i=1;i<=n;++i)
    {
        memset(dp[pos],0,sizeof(dp[pos]));
        for(int s=0;s<(1<<n);++s)
            if(!(s&(s<<1)))
                for(int t=0;t<(1<<n);++t)
                    if(!(t&(t<<1))&&!(t&s)&&!(t&(s<<1))&&!(t&(s>>1)))
                        for(int j=0;j<=k-I[t];++j)
                            dp[pos][t][j+I[t]]+=dp[!pos][s][j];
        pos=!pos;
    }
    ll ans=0;
    for(int i=0;i<1024;++i)
        ans+=dp[!pos][i][k];
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-09-26 20:19:31 NK20240
简单状压dp
居然还会wa在ll上面
==================================================================*/