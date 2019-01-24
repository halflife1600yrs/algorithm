#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
pll ops[1005], tmp[1005];
int x;

bool cmp(pll a, pll b) { return max(a.first, a.second * x) > max(b.first, a.second * x); }

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        for(int i = 0; i < n; ++i) scanf("%lld %lld", &ops[i].first, &ops[i].second);
        sort(ops, ops + n, cmp);
        ll ans = 0, part;
        for(x = 1; x <= n; ++x)
        {
            int a = 0, b = 0;
            part = 0;
            while(a <= x && b <= n - x)
            {
                if(ops[a + b].first > x * ops[a + b].second)
                    part += ops[a + b].first, a++;
                else
                    part += x * ops[a + b].second, b++;
            }
            int i;
            if(a > x)
                for(i = 0; a + b + i < n; ++i)
                    tmp[i] = pll(0, ops[i].second);
            if(b > n - x)
                for(i = 0; a + b + i < n; ++i)
                    tmp[i] = pll(ops[i].first, 0);
            sort(tmp, tmp + i, cmp);
            for(int j = 0; j < i; ++j)
                part += max(tmp[j].first, tmp[j].second * x);
            if(part > ans) ans = part;
        }
        printf("%lld\n", ans);
    }
    return 0;
}