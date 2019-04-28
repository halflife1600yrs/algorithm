#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=2e5+5,MODE=998244353;
ll multi[MAXN],inv[MAXN],imult[MAXN];
int n,x,y;

ll quick_pow(ll base,int up)
{
    ll ans=1;
    while(up)
    {
        if(up&1) ans=ans*base%MODE;
        base=base*base%MODE;
        up>>=1;
    }
    return ans;
}

inline ll C(int n,int k)
{
    return multi[n]*imult[k]%MODE*imult[n-k]%MODE;
}

int main()
{
    multi[0]=1,multi[1]=1,inv[1]=1,imult[0]=1,imult[1]=1;
    scanf("%d %d %d",&n,&x,&y);
    for(int i=2;i<=n;++i)
    {
        multi[i]=multi[i-1]*i%MODE;
        inv[i]=((MODE-MODE/i)*inv[MODE%i])%MODE;
        imult[i]=imult[i-1]*inv[i]%MODE;
    }
    ll ans=1+n;
    ll p0=x*quick_pow(y,MODE-2)%MODE;
    ll p=p0;
    for(int i=2;i<=n;++i)
    { // C(n,k)*(x/y)^k*(1-x/y)^(n-k)
        ans+=p*C(n,i)%MODE;
        ans%=MODE;
        p*=quick_pow(p0,i);
        p%=MODE;
    }
    printf("%lld\n",ans);
    return 0;
}

/*=======================================
added at 2019.Apr27 11:59:11	problem:COJ1530
快速幂幂次爆int会出现死循环,应该用ll
=======================================*/