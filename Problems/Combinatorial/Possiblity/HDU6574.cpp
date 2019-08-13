#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6+5;
const int MODE = 1e9+7;

ll inv[MAXN],prefix[MAXN];

inline ll add(ll x,ll y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

inline ll sum(int x)
{
    return 1ll*x*(x+1)%MODE*inv[2]%MODE;
}

void init()
{
    inv[1] = 1;
    for(int i=2;i<MAXN;++i)
        inv[i] = 1ll*(MODE - MODE/i)*inv[MODE%i]%MODE;
    for(int i=1;i<MAXN;++i)
        prefix[i]=add(prefix[i-1],inv[i]);
}

int main()
{
    init();
    int n;
    while(~scanf("%d",&n))
    {
        ll ans=0;
        for(int i=1;i<=n;++i)
        {
            ll sum1=inv[i]*inv[n]%MODE*sum(i-1)%MODE;
            ll sum2=((n-i)-(i*(prefix[n]-prefix[i])%MODE)%MODE)%MODE;
            if(sum2<0) sum2+=MODE;
            ll sum3=inv[n]*(inv[n]*sum2%MODE+sum1)%MODE;
            (ans+=sum3)%=MODE;
        }
        ans=(1-ans)%MODE;
        if(ans<0) ans+=MODE;
        printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-11 19:34:36 HDU6574
区间内随机选择区间求不相交概率
==================================================================*/