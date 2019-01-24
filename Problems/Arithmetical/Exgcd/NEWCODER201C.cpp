#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll a, b, c, p1, p2, q1, q2;
ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll t = exgcd(b, a % b, x, y);
    ll x0 = x, y0 = y;
    x = y0;
    y = x0 - (a / b) * y0;
    return t;
}
inline ll get_ans(ll x, ll y)
{
    return p2 * x * x + p1 * x + q2 * y * y + q1 * y;
}
int main()
{
    while(~scanf("%lld %lld %lld", &a, &b, &c))
    {
        scanf("%lld %lld", &p1, &p2);
        scanf("%lld %lld", &q1, &q2);
        ll x, y;
        if(!b)
        {
            if(!a)
            {
                if(!c)
                    x = round(-p1 / 2.0f / p2), y = round(-q1 / 2.0f / q2), printf("%lld\n", get_ans(x, y));
                else
                    printf("Kuon\n");
                continue;
            }
            if(c % a == 0)
                x = c / a, y = round(-q1 / 2.0f / q2), printf("%lld\n", get_ans(x, y));
            else
                printf("Kuon\n");
            continue;
        }
        ll g = exgcd(a, b, x, y);
        if(c % g != 0)
        {
            printf("Kuon\n");
            continue;
        }
        x *= c / g, y *= c / g;
        // debug2(x, y);
        ll step = b / g;
        // debug1(step);
        double k1 = p2 + 1.0f * q2 * a / b * a / b, k2 = p1 - 2.0f * q2 * a / b * c / b - 1.0f * q1 * a / b, k3 = -k2 / 2 / k1;
        ll ans = round((k3 - x) / step) * step + x;
        y = (c - a * ans) / b;
        // debug2(ans, y);
        printf("%lld\n", get_ans(ans,y));
    }
    return 0;
}

/*=======================================
added at 2018年10月01日 20:11:03	problem:NEWCODER201C
不用float、、
=======================================*/