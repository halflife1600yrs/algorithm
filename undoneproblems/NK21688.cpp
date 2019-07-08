#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5,INF=0x7f7f7f7f;
int a[55],b[55],c[55];
int dp[MAXN*2];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;++i) scanf("%d",&a[i]);
    for(int i=0;i<n;++i) scanf("%d",&b[i]);
    for(int i=0;i<n;++i) scanf("%d",&c[i]);
    int ans=INF;
    int nxt;
    memset(dp,0x7f,sizeof(dp));
    for(int i=0;i<n;++i)
    {
        for(int j=k;j>0;--j)
        {
            if(dp[j]<INF)
            {
                nxt=min(k,j+a[i]-1);
                dp[nxt]=min(dp[nxt],dp[j]+c[i]);
            }
        }
        nxt=min(k,a[i]-1);
        dp[nxt]=min(dp[nxt],c[i]);
    }
    ans=min(ans,dp[k]);
    memset(dp,0x7f,sizeof(dp));
    for(int i=0;i<n;++i)
    {
        for(int j=k;j>0;--j)
        {
            if(dp[j]<INF)
            {
                nxt=min(k,j+b[i]-1);
                dp[nxt]=min(dp[nxt],dp[j]+c[i]);
            }
        }
        nxt=min(k,b[i]-1);
        dp[nxt]=min(dp[nxt],c[i]);
    }
    ans=min(ans,dp[k]);
    memset(dp,0x7f,sizeof(dp));
    for(int i=0;i<n;++i)
    {
        for(int j=2*k-1,nxt;j>0;--j)
        {
            if(dp[j]<INF)
            {
                nxt=min(2*k-1,j+a[i]+b[i]);
                dp[nxt]=min(dp[nxt],dp[j]+c[i]);
            }
        }
        nxt=min(2*k-1,a[i]+b[i]);
        dp[nxt]=min(dp[nxt],c[i]);
    }
    ans=min(ans,dp[2*k-1]);
    if(ans==0x7f7f7f7f) printf("-1\n");
    else printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-07-07 08:30:21 Problem:NK21688.cpp
每个盒子里有a个红球b个篮球,可能发生偏差
买到k个颜色相同的求至少需要花费多少
考虑最坏的情况,如果要买k个a,那么要按照每个盒子是a-1个进行考虑
同样买k个b也是同样的方式
但是这里漏了一个情况:
在考虑每个盒子是a少了的时候买了k个a,这时可能b已经超过k个了
所以,当盒子里球的总数达到2k-1的时候一定可以买到k个颜色相同的球
怎么证明考虑这三种情况一定可以覆盖到准确解呢?
反证法,假设一种买法不在前三种情况中
即,其中的\sum{a[i]-1}<k,\sum{b[i]-1}<k,\sum{a[i]+b[i]}<2k-1
但它又是一定满足情况的,max{ \sum{a[i]}-x,\sum{b[i]}+x }>=k
其中-m<=x<=m,m是盒子数
显然可得上面这个函数在x=(\sum{a[i]}+\sum{b[i]})/2时函数达到最小值
如果m>=x,那么和第三个条件矛盾
如果m<x,那么最小值为max( \sum{a[i]},\sum{b[i]} )-m>=k和第一第二条件矛盾
==================================================================*/