#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
double sum[MAXN];

int main()
{
    for(int i=1;i<MAXN;++i)
        sum[i]=sum[i-1]+1.0/i;
    for(int T,n,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d",&n);
        printf("Case %d: %.8lf\n",_,n*sum[n]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-20 10:49:09	LightOJ1248
刚开始想用容斥做发现式子太复杂根本推不出来
然后发现只要将事件分解为 已有i面掷出第i+1面的期望 之和,易得
==================================================================*/