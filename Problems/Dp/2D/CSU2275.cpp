#include <bits/stdc++.h>

using namespace std;

double dp[(1<<15)+1000][20];
double ans[20];

int main()
{
    for(int T,_=scanf("%d",&T),n,id;T--;)
    {
        scanf("%d%d%d",&_,&n,&id);
        double pl,pr,pw;
        scanf("%lf%lf",&pl,&pr);
        pw=1-pl-pr;
        dp[0][0]=1;
        for(int i=0;i<n;++i) ans[i]=dp[0][i]*pw;
        int maxi=(1<<n);
        for(int i=1;i<=maxi+400;++i)
        {
            for(int j=0;j<n;++j)
                dp[i][j]=dp[i-1][(j-1+n)%n]*pl+dp[i-1][(j+1)%n]*pr;
            for(int j=0;j<n;++j) ans[j]+=dp[i][j]*pw;
        }
        double sum=0;
        for(int i=0;i<n;++i) sum+=ans[i];
        double ret=ans[id]/sum*100;
        printf("%d %.2f\n",_,ret);
    }
    return 0;
}

/*=======================================
added at 2019.Mar20 12:40:24	problem:CSU2275
概率dp
需要多跑几轮
1
1 6 0 .4 .5
=======================================*/
