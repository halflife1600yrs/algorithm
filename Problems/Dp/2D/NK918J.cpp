#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5,MAXK=1e3+5;
int val[MAXN];
int dp[2][MAXK],sum[2][MAXK];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    scanf("%d",&val[0]);
    int maxi=sum[0][1]=dp[0][1]=val[0];
    bool pos=1;
    for(int i=1;i<n;++i)
    {
        scanf("%d",&val[i]);
        sum[pos][1]=maxi+(dp[pos][1]=val[i]);
        maxi=sum[pos][1];
        for(int j=1;j<min(i+1,k);++j)
        {
            if(dp[!pos][j]<val[i])
            {
                sum[pos][j+1]=sum[!pos][j]+(val[i]-dp[!pos][j])*j+(dp[pos][j+1]=val[i]);
            } else
            {
                sum[pos][j+1]=sum[!pos][j]+(dp[pos][j+1]=dp[!pos][j]);
            }
            if(sum[pos][j+1]>maxi) maxi=sum[pos][j+1];
        }
        pos=!pos;
    }
    printf("%d\n",maxi);
    return 0;
}

/*=======================================
added at 2019.Jun09 10:21:15	problem:NK918J
滚动数组写wa两发，dp题有点生疏了
感觉这个可dp性质可以证明一下？
=======================================*/
/*==================================================================
added at 2019-07-08 10:48:25 NK918J
dp[i][j]表示第i头奶牛是组里第j个的收益和
==================================================================*/