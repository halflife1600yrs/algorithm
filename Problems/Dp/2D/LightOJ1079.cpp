#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5;
double dp[MAXN];

int main()
{
    double p;
    for(int T,n,_=scanf("%d",&T);T--;++_)
    {
        scanf("%lf %d",&p,&n);
        fill(dp,dp+MAXN,1.0);
        int v;
        double pi;
        for(int i=0;i<n;++i)
        {
            scanf("%d %lf",&v,&pi);
            if(i)
                for(int j=MAXN-1;j>=0;--j)
                    if(dp[j]) dp[j+v]=min(dp[j]+pi-pi*dp[j],dp[j+v]);
            dp[v]=min(pi,dp[v]);
        }
        int maxi=0; // 这里没初始化
        for(int i=1;i<MAXN;++i)
            if(dp[i]<p) maxi=i;
        printf("Case %d: %d\n",_,maxi);
    }
    return 0;
}

/*==================================================================
added at 2019-07-19 10:34:35	LOJ1079

==================================================================*/