#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e3+20;
int c[MAXN][MAXN],d[MAXN]; // c[i][j] i j-1->j
ll up[MAXN][MAXN],sum[MAXN]; // up记录每个位置往上升最多能获得多少,sum是一行的和
ll profit[MAXN]; // 全部升到i层收益

int main()
{
    for(int T,n,m,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d %d",&n,&m);
        fill(profit,profit+m+10,0);
        for(int i=0;i<n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&c[i][j]);
                profit[j]-=c[i][j];
            }
        for(int i=1;i<=m;++i) scanf("%d",&d[i]),profit[i]+=(d[i]+profit[i-1]);
        for(int i=0;i<n;++i)
        {
            up[i][m]=0;
            for(int j=m;j>0;--j)
                up[i][j-1]=max(0ll,up[i][j]-c[i][j]);
        }
        fill(sum,sum+m+10,0);
        ll mini;
        for(int i=0,sz;i<m;++i)
        {
            sum[i]=sz=0;
            mini=0x7f7f7f7f7f7f7f7f;
            for(int j=0;j<n;++j)
            {
                if(up[j][i])
                {
                    if(up[j][i]<mini) mini=up[j][i];
                    sum[i]+=up[j][i],++sz;
                }
            }
            if(sz==n) sum[i]-=mini; // 减去一个最小的,保证这里不会全部向上
        }
        ll maxi=0;
        for(int i=0;i<=m;++i)
            if(profit[i]+sum[i]>maxi) maxi=profit[i]+sum[i];
        printf("Case #%d: %lld\n",_,maxi);
    }
    return 0;
}

/*==================================================================
added at 2019-08-04 17:28:50 J
3 2
1 -2
1 -2
1 -2
8 -100
又出现了ll没考虑清楚的事情
==================================================================*/