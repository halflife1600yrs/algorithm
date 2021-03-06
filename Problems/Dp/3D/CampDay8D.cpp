#include <bits/stdc++.h>

typedef long long ll;
const int MODE=998244353;
ll dp[45][45][45][2]={
    // {},
    // {
    //     {{0,0},{0,1}},
    //     {{1,0}}
    // },
    // {
    //     {{0,0},{0,1},{0,1}},
    //     {{1,0},{0,0}},
    //     {{1,0}}
    // },
    // {
    //     {{0,0},{0,1},{0,0},{0,1}},
    //     {{1,0},{1,1},{0,0}},
    //     {{0,0},{0,0}},
    //     {{1,0}}
    // }
};

void init()
{
    dp[1][0][1][1]=1,dp[1][1][0][1]=1;
    dp[2][0][1][1]=1,dp[2][0][2][1]=1;
    dp[2][1][0][0]=1,dp[2][2][0][0]=1;
    dp[3][0][1][1]=1,dp[3][0][3][1]=1;
    dp[3][1][0][0]=1,dp[3][1][1][0]=1,dp[3][1][1][1]=1;
    dp[3][3][0][0]=1;
}

int main()
{
    init();
    for(int k=4;k<42;++k)
        for(int i=0;i<=k;++i)
            for(int j=0;j<=k-i;++j)
            {
                if(i)
                {
                    dp[k][i][j][0]=dp[k-1][i-1][j][0];
                    if(i+j-1<=k-3)
                        dp[k][i][j][0]=(dp[k][i][j][0]+(dp[k-3][i-1][j][0]+dp[k-3][i-1][j][1])%MODE)%MODE;
                }
                if(j)
                {
                    dp[k][i][j][1]=dp[k-1][i][j-1][1];
                    if(i+j-1<=k-3)
                        dp[k][i][j][1]=(dp[k][i][j][1]+(dp[k-3][i][j-1][0]+dp[k-3][i][j-1][1])%MODE)%MODE;
                }
            }
    int n;
    scanf("%d",&n);
    if(n==1)
    {
        printf("1\n");
        return 0;
    }
    ll ans=0;
    for(int i=0;i<n;++i)
        ans=(ans+(dp[2*n][i][i][0]+dp[2*n][i][i][1])%MODE)%MODE;
    for(int i=0;i<n-1;++i)
        ans=(ans+(dp[2*n-2][i][i][0]+dp[2*n-2][i][i][1])%MODE)%MODE;
    printf("%lld\n",ans);
    return 0;
}

/*=======================================
added at 2019.Jan28 00:14:37	problem:d
dp[k][i][j][0/1]表示k位,有i个l,j个r,且结尾为l(0)或r(1)的满足条件的序列数
条件为:没有l和r相邻且空格的连续个数一定为2
递推公式为:
dp[k][i][j][0]=dp[k-1][i-1][j][0]+dp[k-3][i-1][j][0]+dp[k-3][i-1][j][1]
dp[k][i][j][1]=dp[k-1][i][j-1][1]+dp[k-3][i][j-1][0]+dp[k-3][i][j-1][1]
得到结果需要对所有dp[k][i][i]([0]+[1])和dp[k-2][i][i]([0]+[1])求和
表为:6 14 38 100 268 726 1974 5404 14852 40972 113388
注意特判1
初始化要写在程序中
=======================================*/