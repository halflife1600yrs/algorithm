#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
ll inv(int x)
{
    ll base = x, tmp = MOD - 2, ans = 1;
    while(tmp)
    {
        if(tmp & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        tmp >>= 1;
    }
    return ans;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        ll ans1 = 1, ans2 = 1;
        int x, y;
        for(int i = 0; i < n; i++)
        {
            scanf("%d %d", &x, &y);
            ans1 = (ans1 * (y - x)) % MOD;
            ans2 = (ans2 * y) % MOD;
        }
        printf("%lld\n", ((ans2 - ans1 + MOD) % MOD) * inv(ans2) % MOD);
    }
    return 0;
}