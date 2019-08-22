#include <bits/stdc++.h>

typedef long long ll;
const int MODE=1e9+7,inv6=166666668;

int main()
{
    ll n;
    while(~scanf("%lld",&n))
    {
        n%=MODE;
        printf("%lld\n",n*(ll)(n+1)%MODE*(2*n+1)%MODE*inv6%MODE);
    }
    return 0;
}