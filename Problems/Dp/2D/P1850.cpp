#include <bits/stdc++.h>
using namespace std;

const int MAXN=2005,MAXV=303,MAXE=MAXV*MAXV;
const double INF=1e7,EPS=1e-8;
int n,m,v,e;
int room[2][MAXN];
int land[MAXV][MAXV];
double rate[MAXN],dp[MAXN][MAXN][2];
void floyed()
{
    for(int k = 1; k <= v; ++k)
        for(int i = 1; i <= v; ++i)
            for(int j = 1; j <= v; ++j)
                if(land[i][k] + land[k][j] < land[i][j])
                    land[i][j] = land[i][k] + land[k][j];
}
int main()
{
    scanf("%d %d %d %d",&n,&m,&v,&e);
    for(int i=1;i<=n;++i) scanf("%d",&room[0][i]);
    for(int i=1;i<=n;++i) scanf("%d",&room[1][i]);
    for(int i=1;i<=n;++i) scanf("%lf",&rate[i]);
    for(int i=1;i<v;++i)
        for(int j=i+1;j<=v;++j)
            if(i==j) land[i][i]=0;
            else land[i][j]=land[j][i]=1e7;
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        land[fr][to]=land[to][fr]=min(land[fr][to],l);
    }
    floyed();
    dp[1][0][1]=dp[1][1][0]=INF;
    for(int i=2;i<=n;++i)
    {
        dp[i][0][0]=dp[i-1][0][0]+land[ room[0][i-1] ][ room[0][i] ];
        dp[i][0][1]=INF;
        for(int j=1;j<=min(i,m);++j)
        {
            dp[i][j][1]=min(
                dp[i-1][j-1][0]
                +rate[i]*land[ room[0][i-1] ][ room[1][i] ]
                +(1-rate[i])*land[ room[0][i-1] ][ room[0][i] ]
                ,
                dp[i-1][j-1][1]
                +rate[i-1] * rate[i] * land[ room[1][i-1] ][ room[1][i] ]
                +(1-rate[i-1]) * rate[i] * land[ room[0][i-1] ][ room[1][i] ]
                +rate[i-1] * (1-rate[i]) * land[ room[1][i-1] ][ room[0][i] ]
                +(1-rate[i-1]) * (1-rate[i]) * land[ room[0][i-1] ][ room[0][i] ]
            );
            if(j<i) dp[i][j][0]=min(
                dp[i-1][j][0]
                +land[ room[0][i-1] ][ room[0][i] ]
                ,
                dp[i-1][j][1]
                +rate[i-1]*land[ room[1][i-1] ][ room[0][i] ]
                +(1-rate[i-1])*land[ room[0][i-1] ][ room[0][i] ]
            );
            else dp[i][j][0]=INF;
        }
    }
    double ans=dp[n][0][0];
    for(int i=1;i<=min(n,m);++i)
    {
        ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
    }
    printf("%.2lf\n",ans);
    return 0;
}

/*=======================================
added at 2018年9月28日 11:54:03	problem:P1850
没有考虑到相邻的点同时取到的问题
=======================================*/
/*==================================================================
added at 2019-08-07 21:06:16	P1850
一年
总算把这题补了
==================================================================*/