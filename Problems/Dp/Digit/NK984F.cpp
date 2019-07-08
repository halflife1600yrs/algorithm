#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[32][32]; // dp[i][j]i个位置放大于等于j个0的方法数
ll pows[32];

ll get_ans(int x)
{
    if(x<=1) return 0;
    ll ans=0;
    int num0=-1,f1=30,aim;
    while(!(x&pows[f1])) --f1;
    // debug1(f1);
    for(int i=f1-1;i>=0;--i)
    { // 从最前面的1后面的一个位置开始找
        if(!(x&pows[i]))
        {
            ++num0;
            continue;
        } else
        {
            ++num0; // 把这个位置置为0,然后后面放0
            aim=max(0.0,ceil((i-num0)/2.0));
            ans+=dp[i][aim]; // 每位的贡献是这个位为0后面填0的方法数
            num0-=2; // 然后变回1
        }
    }
    if(num0>=0) ++ans; // 这个数本身是不是满足条件
    for(int i=f1-1;i>=1;--i)
    {
        aim=max(0.0,ceil((i+1)/2.0));
        ans+=dp[i][aim];
    }
    return ans; // 加上首位为1，其余为0的情况
}

int main()
{
    for(int i=0;i<32;++i) dp[i][0]=1,pows[i]=1ll<<i;
    for(int i=1;i<32;++i)
        for(int j=1;j<=i;++j)
            dp[i][j]=dp[i-1][j]+dp[i-1][j-1]; // 组合数
    for(int i=1;i<32;++i)
        for(int j=i-1;j>=0;--j)
            dp[i][j]=dp[i][j]+dp[i][j+1];
    int l,r;
    scanf("%d %d",&l,&r);
    printf("%lld\n",get_ans(r)-get_ans(l-1));
    return 0;
}

/*==================================================================
added at 2019-07-06 19:26:02 Problem:NK984F.cpp
2进制的数位dp
求一个范围0多于1的数的数量
分清楚情况是比较重要的:
1. 除了第1位,每个1位的贡献是它为0,后面填若干个0使0多于1的方法,是组合数加和
2. 首位为0的贡献不能这样算因为这会导致前导0,需要对后面每位枚举这位为1,前面
全为0后面按限制填0的方法数,也是组合数加和
3. 最后再判断原数是不是满足条件的
4. 1位为1后面全0的情况不需要算,因为它已经包含在后面一个1位为1且后面全填0的
情况中
==================================================================*/