```c++
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
```

### 食用注意

1. 直接调用NTT::work()即可，参数为两个乘数多项式`p1`, `p2`和一个积多项式`p3`，`p3`用于存放答案。实现了多项式的自动变长，但前提是参数传入时`p1`,`p2`需要预先resize为正确的长度
2. `p1`,`p2`,`p3`两两可以相等
3. resort数组的大小应该为比多项式积的长度大的最小的2的整数幂
4. vector的第i项是多项式的i次项

### NTT的限制:
- 所求的多项式要求是整系数
- 如果题目要求结果对质数p取模,这个质数往往只能是998244353，否则会有很多麻烦，这个会在后面谈到.
- 所求多项式的项数应在$2^{23}$之内,因为$998244353=7∗17∗2^{23}+1$,而998244353的k次元根为$3^{(998244353-1)/k}$,在多项式乘法中这个k一般是2的整数次幂
- 结果的系数不应超过质数P.(P是自己选择的质数,一般定为P=998244353)
