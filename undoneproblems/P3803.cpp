#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXL = 2097155, MODE = 998244353, g = 3; // 元根

namespace NTT
{
typedef long long ll;
int lenz, resort[MAXL]; // lenz是积多项式的次数界,也就是大于等于n+m+1的最小2的幂
int v1[MAXL], v2[MAXL];

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

void transform(int* p, int pattern)
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

void work(int* p1, int* p2, int* p3, int l1, int l2)
{
    init(l1 + l2);
    for(int i = 0; i < lenz; ++i)
    {
        if(resort[i] <= l1) v1[i] = p1[resort[i]];
        if(resort[i] <= l2) v2[i] = p2[resort[i]];
    }
    transform(v1, 1), transform(v2, 1);
    for(int i = 0; i < lenz; ++i)
        p3[i] = v1[resort[i]] * 1ll * v2[resort[i]] % MODE;
    transform(p3, -1);
    for(int i = 0, k = quick_pow(lenz, MODE - 2); i < lenz; ++i)
        p3[i] = p3[i] * 1ll * k % MODE;
}

} // namespace NTT

int p1[MAXL], p2[MAXL], p3[MAXL];

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= n; ++i) scanf("%d", &p1[i]);
    for(int i = 0; i <= m; ++i) scanf("%d", &p2[i]);
    NTT::work(p1, p2, p3, n, m);
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
4 4
1 6 3 4 9
1 6 3 4 9
1 2
1 2
1 2 3
==================================================================*/