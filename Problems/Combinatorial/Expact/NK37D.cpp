#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int MODE=1e9+7;
typedef long long ll;

ll quickpow(ll base,ll ind)
{
    ll ans=1;
    for(;ind;base=base*(ll)base%MODE,ind>>=1)
        if(ind&1) ans=ans*base%MODE;
    return ans;
}

int main()
{
    ll n;
    while(~scanf("%lld",&n))
        printf("%d\n",quickpow(2,n-3)*(n%MODE)%MODE*((n-1)%MODE)%MODE);
    return 0;
}