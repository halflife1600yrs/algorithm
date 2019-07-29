#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5, MODE = 998244353, g = 3;
typedef long long ll;

vector<int> p, r;

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
const int MAXL = 2097155, MODE = 998244353, g = 3; // 元根
typedef long long ll;
typedef vector<int> vi;
int lenz, resort[MAXL]; // lenz是积多项式的次数界,也就是大于等于n+m+1的最小2的幂

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

void init(int x)
{
    lenz = 1;
    int l = 0;
    while(lenz <= x) lenz <<= 1, ++l;
    for(int i = 1; i < lenz; i++)
        resort[i] = (resort[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

void transform(vi& p, int pattern)
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

void work(const vi& p1, const vi& p2, vi& p3, size_t n = MAXL)
{ // n是多项式对x^n取模
    size_t l1 = min(n, p1.size()), l2 = min(n, p2.size());
    init(l1 + l2 - 2);
    vi v1 = vi(lenz, 0), v2 = vi(lenz, 0);
    for(int i = 0; i < lenz; ++i)
    {
        if(resort[i] < l1) v1[i] = p1[resort[i]];
        if(resort[i] < l2) v2[i] = p2[resort[i]];
    }
    transform(v1, 1), transform(v2, 1);
    p3 = vi(lenz, 0);
    for(int i = 0; i < lenz; ++i)
        p3[i] = v1[resort[i]] * 1ll * v2[resort[i]] % MODE;
    transform(p3, -1);
    for(int i = 0, k = quick_pow(lenz, MODE - 2); i < lenz; ++i)
        p3[i] = p3[i] * 1ll * k % MODE;
    p3.resize(min(n, l1 + l2 - 1));
}

} // namespace NTT

void polyinv(const vector<int>& p, vector<int>& r)
{
    int index = p.size(), l = 1;
    vector<int> inv1(1, quick_pow(p[0], MODE - 2)), inv2;
    while(l < index)
    {
        l <<= 1;
        inv1.resize(l);
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

namespace io
{
const int SIZE = 1e7 + 10;
char inbuff[SIZE];
char *l, *r;
inline void init()
{
    l = inbuff;
    r = inbuff + fread(inbuff, 1, SIZE, stdin);
}
inline char gc()
{
    if(l == r) init();
    return (l != r) ? *(l++) : EOF;
}
void read(int& x)
{
    x = 0;
    char ch = gc();
    while(!isdigit(ch)) ch = gc();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
}
}
using io::read;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n;
    read(n);
    p.reserve(1.5 * n);
    for(int i = 0, x; i < n; ++i) read(x), p.push_back(x);
    polyinv(p, r);
    for(int i = 0; i < n; ++i) printf("%d ", r[i]);
    // cout << endl << clock() << endl;
    return 0;
}
/*==================================================================
added at 2019-07-28 15:05:56 P4238
1 12 42 44 75 132 70 72 81
5
1 6 3 4 9
==================================================================*/