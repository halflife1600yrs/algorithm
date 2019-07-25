#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e3+5;
double dp[MAXN][MAXN];

inline double C2x(int x) { return (x*(x-1))>>1; }

int main()
{
    for(int i=0;i<MAXN;++i) dp[0][i]=1.0,dp[1][i]=0.0;
    double p1,p2,tmp;
    for(int t=2;t<MAXN;++t)
        for(int d=0;d<MAXN;++d)
        {
            tmp=C2x(t+d+1);
            p1=dp[t-2][d]*C2x(t)/tmp+dp[t][d-1]*t*d/tmp;
            p2=p1+dp[t][d-1]*d/tmp;
            dp[t][d]=max(p2/(1.0-C2x(d)/(double)tmp),p1/(1.0-(C2x(d)+d)/(double)tmp));
        }
    for(int T,t,d,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d %d",&t,&d);
        printf("Case %d: %.8lf\n",_,dp[t][d]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-20 11:56:02	LightOJ1265
乘二写成除二了
这题不知道怎么推的,只会写dp暂时
==================================================================*/