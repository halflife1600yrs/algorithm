#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll dp[2][125];

ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(!n)
        {
            printf("1/1\n");
            continue;
        }
        memset(dp[1],0,sizeof(dp[1]));
        dp[1][1]=dp[1][2]=dp[1][3]=dp[1][4]=1;
        bool pos=0;
        for(int i=2;i<=n;++i)
        {
            memset(dp[pos],0,sizeof(dp[pos]));
            for(int j=0;j<=4*n;++j)
            {
                for(int k=1;k<=4;++k)
                    if(k<=j) dp[pos][j]+=dp[!pos][j-k];
            }
            pos=!pos;
        }
        ll up=0,down=0;
        for(int i=0;i<=4*n;++i)
        {
            down+=dp[n&1][i];
            if(i>=3*n) up+=dp[n&1][i];
        }
        // printf("\n");
        ll g=gcd(up,down);
        printf("%lld/%lld\n",up/g,down/g);
    }
    return 0;
}