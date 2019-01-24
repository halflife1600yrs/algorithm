#include <bits/stdc++.h>

using namespace std;

#define debug1(x) cout << #x "=" <<x<< endl;
#define debug2(x,y) cout << #x "=" << x << "," #y "=" << y << endl;
typedef long long ll;
ll mode = 1;
const int sz = 1e5 + 5;
ll inv3;

ll quick_mul(ll a,ll b)
{
    ll ans = 1;
    while(b)
    {
        if(b&1)
            ans = (ans + a) % mode;
        a = (a << 1) % mode, b >>= 1;
    }
    return ans;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if (b == 0) {x = 1;y = 0;return a;}
    ll t = exgcd(b,a % b,x,y);
    ll x0 = x,y0 = y;
    x = y0;y = x0 - (a / b) * y0;
    return t;
}

ll get_sum_squ(ll x)
{
    ll ans;
    if(x&1)
        ans = quick_mul(quick_mul(x, (x + 1) >> 1), 2 * x + 1);
    else
        ans = quick_mul(quick_mul(x >> 1, x + 1), 2 * x + 1);
    if(mode%3==0)
        ans /= 3;
    else
        ans = quick_mul(ans, inv3);
    return ans;
}

int main()
{
    ll n;
    while(~scanf("%lld %lld",&n,&mode))
    {
        ll ans;
        if(n&&1)
            ans = quick_mul(quick_mul(n, (n + 1) >> 1), quick_mul((n + 1) >> 1, n + 2));
        else
            ans = quick_mul(quick_mul(n >> 1, n + 1), quick_mul(n + 1, (n + 2) >> 1));
        if(mode%3==0)
            ans /= 3;
        else 
        {
            ll y;
            exgcd(3, mode, inv3, y);
            ans = quick_mul(ans, inv3);
        }
        debug1(ans);
        ll des = 0,upper = sqrt(n);
        for (int i = 2; i <= upper;i++)
        {
            ll tmp1 = (ll)sqrt(n / (i * i)), tmp2 = n / quick_mul(i, i);
            ll sum1 = get_sum_squ(tmp1);
            des = (des + i * i % mode * (tmp2 * (tmp2 + 1) / 2 % mode-sum1+mode)) % mode;
        }
        debug1(des);
        ans = (ans - des + mode) % mode;
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}

/*=======================================
added at 2018年9月12日 14:16:21	problem:shenyangc
也是跟筛法有点像的
思路还没理清，过几天再看题解
=======================================*/