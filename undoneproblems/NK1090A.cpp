#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;

int lenz(int x)
{
    for(int i=61;i>=0;--i)
        if(x&(1ll<<i)) return i+1;
    return 0;
}

int rev(ll x)
{
    ll ans=0;
    int i,j;
    for(i=61;i>=0;--i)
        if(x&(1ll<<i)) break;
    for(j=0;i>=0;--i,++j)
        if(x&(1ll<<i))
            ans+=1ll<<j;
    return ans;
}

int inv(ll x)
{
    int i;
    for(i=61;i>=0;--i)
        if(x&(1ll<<i)) break;
    for(;i>=0;--i)
        if(x&(1ll<<i)) x-=1ll<<i;
        else x+=1ll<<i;
    return x;
}

int main()
{
    int n;
    ll x;
    scanf("%d",&n);
    // debug1(inv(5));
    while(n--)
    {
        scanf("%lld",&x);
        int l=lenz(x);
        if(l&1)
        {
            l=l/2*2;
            printf("%lld\n",(1ll<<(l/2))-1);
        } else
        {
            ll ans=(1ll<<(l/2))-1;
            ll pre=x>>(l/2);
            ll suf=x^(pre<<(l/2));
            // debug2(pre,suf);
            // debug2(inv(suf),rev(pre));
            if(inv(suf)>rev(pre)) ans+=pre-1-(1ll<<(l/2)-1);
            else ans+=pre-(1ll<<(l/2)-1);
            printf("%lld\n",ans);
        }
    }
    return 0;
}