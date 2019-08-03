#include <bits/stdc++.h>

using namespace std;

const int MODE = 998244353;
typedef long long ll;
typedef vector<int> poly;

ll quick_pow(int x, int up)
{
    ll ans = 1, base = x;
    while(up)
    {
        if(up & 1) ans = ans * base % MODE;
        base = base * base % MODE;
        up >>= 1;
    }
    return ans;
}

namespace NTT
{
const int MAXL = 262150, g = 3; // 元根
int lenz, resort[MAXL]; // lenz是积多项式的次数界,也就是大于等于n+m+1的最小2的幂

void init(int x)
{
    lenz = 1;
    int l = 0;
    while(lenz <= x) lenz <<= 1, ++l;
    for(int i = 1; i < lenz; i++)
        resort[i] = (resort[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

void transform(poly& p, int pattern)
{
    ll base, step, x, y;
    for(int i = 1; i < lenz; i <<= 1)
    {
        step = quick_pow(g, (MODE - 1) / (i << 1));
        if(pattern == -1) step = quick_pow(step, MODE - 2); // 逆DFT的时候乘的是逆元
        for(int j = 0; j < lenz; j += (i << 1))
        {
            base = 1;
            for(int k = 0; k < i; k++)
            {
                x = p[j + k], y = base * p[j + k + i] % MODE;
                p[j + k] = (x + y) % MODE;
                p[j + k + i] = (x - y + MODE) % MODE;
                (base *= step) %= MODE;
            }
        }
    }
}

void work(const poly& p1, const poly& p2, poly& p3, size_t n = MAXL)
{ // n是多项式对x^n取模
    size_t l1 = min(n, p1.size()), l2 = min(n, p2.size());
    init(l1 + l2 - 2);
    poly v1 = poly(lenz, 0), v2 = poly(lenz, 0);
    for(int i = 0; i < lenz; ++i)
    {
        if(resort[i] < l1) v1[i] = p1[resort[i]];
        if(resort[i] < l2) v2[i] = p2[resort[i]];
    }
    transform(v1, 1), transform(v2, 1);
    p3.resize(lenz);
    for(int i = 0; i < lenz; ++i)
        p3[i] = v1[resort[i]] * 1ll * v2[resort[i]] % MODE;
    transform(p3, -1);
    for(int i = 0, k = quick_pow(lenz, MODE - 2); i < lenz; ++i)
        p3[i] = p3[i] * 1ll * k % MODE;
    p3.resize(min(n, l1 + l2 - 1));
}

} // namespace NTT

poly f, g, q, r;

void polyinv(const poly& p, poly& r)
{
    int index = p.size(), l = 1;
    poly inv1(1, quick_pow(p[0], MODE - 2)), inv2;
    while(l < index)
    {
        l <<= 1;
        inv1.resize(l); // 这步不能漏
        NTT::work(inv1, inv1, inv2, l);
        NTT::work(inv2, p, inv2, l);
        for(int i = 0; i < l; ++i)
        {
            inv2[i] = (2ll * inv1[i] - inv2[i]) % MODE;
            if(inv2[i] < 0) inv2[i] += MODE;
        }
        inv1.swap(inv2);
    }
    r.swap(inv1);
}

void polymod(const poly& f, const poly& g, poly& q, poly& r)
{
    poly rev;
    for(int i = g.size() - 1; i >= 0; --i) rev.push_back(g[i]);
    rev.resize(f.size() - g.size() + 1); // 这步不能漏
    polyinv(rev, q);
    rev.resize(0);
    for(int i = f.size() - 1; i >= 0; --i) rev.push_back(f[i]);
    NTT::work(rev, q, q, f.size() - g.size() + 1);
    reverse(q.begin(), q.end());
    NTT::work(g, q, rev);
    r.resize(g.size() - 1);
    for(int i = 0; i < rev.size(); ++i)
    {
        r[i] = ((i < f.size() ? f[i] : 0) - rev[i]) % MODE;
        if(r[i] < 0) r[i] += MODE;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0, x; i <= n; ++i) scanf("%d", &x), f.push_back(x);
    for(int i = 0, x; i <= m; ++i) scanf("%d", &x), g.push_back(x);
    polymod(f, g, q, f);
    for(int i : q) printf("%d ", i);
    printf("\n");
    for(int i : f) printf("%d ", i);
    return 0;
}

/*==================================================================
added at 2019-07-29 16:58:12 P4512
多项式取模
1 2
1 1 
1 2 3
==================================================================*/