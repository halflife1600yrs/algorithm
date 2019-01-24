#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int mode = 1e9 + 7;

ll quick_pow(ll x,ll k)
{
    ll ans = 1;
    while(k)
    {
        if(k&1)
            ans = ans * x % mode;
        x = x * x % mode;
        k >>= 1;
    }
    return ans;
}

int main()
{
    int cas, n, m;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d%d", &n, &m);
        ll tmp1 = (quick_pow(2, m) - 1 + mode) % mode;
        ll ans = quick_pow(tmp1, n);
        if(n&1)
            ans = (ans + 1) % mode;
        else
            ans = (ans + tmp1) % mode;
        printf("%lld\n", ans);
    }
    return 0;
}

/*=======================================
added at 2018年9月12日  13:58:52
能想到大概是容斥定理，但是具体规律是打表找的
需要再推一遍
=======================================*/