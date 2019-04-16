#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7;

inline ll sum(int x) { return ((1ll*x*(x+1))>>1)%MODE; }

int main()
{
    int n;
    scanf("%d",&n);
    ll ans=0,a;
    for(int i=0;i<n;++i)
    {
        scanf("%lld",&a);
        ans+=sum(n-i)*(i+1)%MODE*a%MODE;
        ans%=MODE;
    }
    printf("%lld\n",ans);
    return 0;
}

/*=======================================
added at 2019.Apr16 13:57:59	problem:2050WarmingUpB
简单地计算贡献
=======================================*/