#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAXN=36;
ull dp[MAXN][MAXN]; // dp[i][j]节点为i高度大于等于j

void init()
{
    dp[1][1]=dp[0][0]=1;
    dp[2][2]=2;
    for(int i=3;i<MAXN;++i)
    {
        for(int h=1;h<MAXN;++h)
        {
            dp[i][h]=0;
            for(int j=0;j<i;++j)
            {
                for(int l=0;l<h;++l) // 左边的高度为h
                {
                    if(j==i-1-j&&l==h-1) {}// 防止左右算重复了
                    else
                    {
                        dp[i][h]+=dp[j][h-1]*dp[i-1-j][l];
                    }
                }
                for(int l=0;l<h-1;++l) // 右边的高度为h
                {
                    if(j==i-1-j&&l==h-1) {}
                    else
                    {
                        dp[i][h]+=dp[j][l]*dp[i-1-j][h-1];
                    }
                }
            }
            if(i&1) dp[i][h]+=dp[(i-1)/2][h-1]*dp[(i-1)/2][h-1]; // 单独处理左右一样高
        }
    }
}

int n,h;

int main()
{
    init();
    int n,h;
    while(~scanf("%d %d",&n,&h))
    {
        ull ans=0;
        for(int i=n;i>=h;--i) ans+=dp[n][i];
        printf("%llu\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-03 19:56:29 B
非完全的卡特兰数
n比较小所以直接四维dp
==================================================================*/