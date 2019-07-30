#include <bits/stdc++.h>

using namespace std;

const int MODE = 998244353;
typedef vector<int> poly;
typedef long long ll;

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
const int MAXL = 2097155, g = 3; // 元根
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
    p3 = poly(lenz, 0);
    for(int i = 0; i < lenz; ++i)
        p3[i] = v1[resort[i]] * 1ll * v2[resort[i]] % MODE;
    transform(p3, -1);
    for(int i = 0, k = quick_pow(lenz, MODE - 2); i < lenz; ++i)
        p3[i] = p3[i] * 1ll * k % MODE;
    p3.resize(min(n, l1 + l2 - 1));
}

} // namespace NTT

poly p1, p2, p3;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0, x; i <= n; ++i) scanf("%d", &x), p1.push_back(x);
    for(int i = 0, x; i <= m; ++i) scanf("%d", &x), p2.push_back(x);
    NTT::work(p1, p2, p3);
    for(int i = 0; i <= n + m; ++i) printf("%d ", p3[i]);
    return 0;
}
/*==================================================================
added at 2019-07-28 11:22:50 P3803_NTT
NTT模板,用了vector跑的还比FFT还快
NTT的限制:
- 所求的多项式要求是整系数
- 如果题目要求结果对质数p取模,这个质数往往只能是998244353，否则会有很多麻烦，这个会在后面谈到.
- 所求多项式的项数应在223223 之内,因为998244353=7∗17∗223+1998244353=7∗17∗223+1
- 结果的系数不应超过质数P.(P是自己选择的质数,一般定为P=998244353)
1 1
855638017 305585006
7 1

5 1
8 0 6 2 9 1
855638017 305585006

4 1
325957341 550053011 142606337 448191342 855638018
1 7

1 2
1 2
1 2 1
==================================================================*/