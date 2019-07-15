#include <bits/stdc++.h>

using namespace std;

const int MAXN=4e3+5,STATE=12900;
int c[MAXN],w[MAXN];
int dp[STATE];

int main()
{
    int n,h;
    scanf("%d%d",&n,&h);
    for(int i=0;i<n;++i)
    {
        scanf("%d %d",&c[i],&w[i]);
        for(int j=h;j>0;--j)
            if(dp[j]&&j+c[i]<=h)
                dp[j+c[i]]=max(dp[j+c[i]],dp[j]+w[i]);
        dp[c[i]]=max(dp[c[i]],w[i]);
    }
    int ans=0;
    for(int i=0;i<=h;++i) ans=max(dp[i],ans);
    printf("%d\n",ans);
    return 0;
}