#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
bool seive[MAXN];
double dp[MAXN];
int pri[MAXN],d[MAXN],num[MAXN],pnum=0;

int main()
{
    for(int i=2;i<MAXN;++i)
    { // 线性筛筛一下因子数
        if(!seive[i]) pri[pnum++]=i,num[i]=1,d[i]=2;
        for(int j=0;j<pnum&&i*pri[j]<MAXN;++j)
        {
            seive[i*pri[j]]=1;
            if(i%pri[j]==0)
            {
                num[i*pri[j]]=num[i]+1;
                d[i*pri[j]]=d[i]/(num[i]+1)*(num[i*pri[j]]+1);
                break;
            }
            num[i*pri[j]]=1;
            d[i*pri[j]]=d[i]*2;
        }
    }
    for(int i=2,m;i<MAXN;++i)
    { // 对每个数的倍数做转移
        m=d[i];
        dp[i]+=1.0/m;
        dp[i]=(dp[i]*m+1.0)/(m-1); // 这里处理转移到自己的情况,相当于解方程
        for(int j=2*i;j<MAXN;j+=i)
            dp[j]+=(dp[i]+1.0)/d[j];
    }
    for(int T,n,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        printf("Case %d: ",_);
        if(n==1) printf("0\n");
        else printf("%.8f\n",dp[n]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-18 00:00:13	LOJ1038
线性预处理因数数量然后nlogn预处理因数转移
==================================================================*/