#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

typedef long long ll;
ll pows[64];

int main()
{
    for(int i=pows[0]=1;i<64;++i) pows[i]=pows[i-1]<<1;
    int T,n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double p;
        m=0;
        for(int i=0;i<n;++i)
        {
            scanf("%lf",&p);
            if(p!=0.5) ++m;
        }
        printf("%lld\n",pows[n]-pows[m]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-09 16:48:27 NK16604
可以用数学归纳法推导出集合里的所以p一定是0.5
==================================================================*/