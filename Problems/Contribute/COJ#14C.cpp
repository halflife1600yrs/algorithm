#include <algorithm>
#include <iostream>
#include <cstring>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>
#include <map>

using namespace std;

const int MAXN=2e3+5,MODE=20050321;
int pows[MAXN],spow[MAXN];
int dp[MAXN][MAXN];

int main()
{
    int n,q,l,r;
    scanf("%d %d",&n,&q);
    for(int i=pows[0]=spow[0]=1;i<=max(n,q);++i)
        pows[i]=(pows[i-1]<<1)%MODE,spow[i]=pows[i]+spow[i-1];
    for(int i=1;i<=n;++i) dp[i][0]=0;
    for(int i=1;i<=q;++i)
    {
        scanf("%d %d",&l,&r);
        int ans=0;
        for(int j=1;j<=n;++j)
        {
            if(l<j&&j<=r) dp[j][i]=dp[j][i-1];
            else if((j==l&&j>1)||j==r+1) dp[j][i]=(pows[i-1]+dp[j][i-1])%MODE;
            else dp[j][i]=(dp[j][i-1]<<1)%MODE;
            ans=(ans+dp[j][i])%MODE;
        }
        printf("%d\n",(ans+pows[i])%MODE);
    }
    return 0;   
}

/*==================================================================
added at 2019-11-08 20:45:47 C
算贡献及其巧妙的题目
计算相邻的两个数在哪些情况下可以产生变化
需要考虑每次操作后在端点上、不被覆盖和被覆盖三种情况
==================================================================*/