#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5,MODE=100003;
int dp[MAXN];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    dp[0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=max(0,i-k);j<i;++j)
        {
            dp[i]+=dp[j];
            dp[i]%=MODE;
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}