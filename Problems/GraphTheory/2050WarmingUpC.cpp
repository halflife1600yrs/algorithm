#include <bits/stdc++.h>

typedef long long ll;
const int MODE=1e9+7;

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n==1) printf("0\n");
        else printf("%lld\n",(((1ll*n*(n+1))>>1)-1+MODE)%MODE);
    }
    return 0;
}

/*=======================================
added at 2019.Apr16 13:58:50	problem:2050WarmingUpC
考察图论联通性质
=======================================*/