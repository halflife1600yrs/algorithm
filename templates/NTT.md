```c++
#include <bits/stdc++.h>

using namespace std;

const int MODE = 998244353;
typedef long long ll;
typedef vector<int> poly;
typedef vector<int>::iterator vit;

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
    p3.resize(lenz); // 这里resize使得p3可以和p1,p2相等
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
{ // 多项式求逆
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

void polymod(const poly& f, const poly& mod, poly& r)
{ // 如何想要获取一个q的话再传一个进来就行了
    if(mod.size()>f.size())
    {
        r=f;
        return;
    }
    poly q, rev;
    for(int i = mod.size() - 1; i >= 0; --i) rev.push_back(mod[i]);
    rev.resize(f.size() - mod.size() + 1); // 这步不能漏
    polyinv(rev, q);
    rev.resize(0);
    for(int i = f.size() - 1; i >= 0; --i) rev.push_back(f[i]);
    NTT::work(rev, q, q, f.size() - mod.size() + 1);
    reverse(q.begin(), q.end());
    NTT::work(mod, q, rev);
    r.resize(mod.size() - 1);
    for(int i = 0; i < rev.size(); ++i)
    {
        r[i] = ((i < f.size() ? f[i] : 0) - rev[i]) % MODE;
        if(r[i] < 0) r[i] += MODE;
    }
}
```

### 食用注意

1. 直接调用NTT::work()即可，参数为两个乘数多项式`p1`, `p2`和一个积多项式`p3`，`p3`用于存放答案。实现了多项式的自动变长，但前提是参数传入时`p1`,`p2`需要预先resize为正确的长度
2. `p1`,`p2`,`p3`两两可以相等
3. resort数组的大小应该为比多项式积的长度大的最小的2的整数幂
4. vector的第i项是多项式的i次项
2. **多项式在使用的时候一定要resize到你需要的大小**。
3. 多项式求逆的两个参数`p`和`r`可以相同
4. 多项式取模的四个参数`f`,`g`,`r`，`r`、`f`和`g`可以两两相等。

### NTT的限制:
- 所求的多项式要求是整系数
- 如果题目要求结果对质数p取模,这个质数往往只能是998244353，否则会有很多麻烦，这个会在后面谈到.
- 所求多项式的项数应在$2^{23}$之内,因为$998244353=7∗17∗2^{23}+1$,而998244353的k次元根为$3^{(998244353-1)/k}$,在多项式乘法中这个k一般是2的整数次幂
- 结果的系数不应超过质数P.(P是自己选择的质数,一般定为P=998244353)

### 测试数据

NTT

```
input				output
5 5					8 64 90 50 113 160 105 64 61 65 20 
1 7 4 0 9 4 
8 8 2 4 5 5
```

求逆

```
input				output
5					1 998244347 33 998244169 1020
1 6 3 4 9
```

取模

```
input				output
5 1					237340659 335104102 649004347 448191342 855638018
1 9 2 6 0 8			 760903695
1 7
```

### NTT模数原根表

```
（g 是mod(r*2^k+1)的原根）

素数  r  k  g
3   1   1   2
5   1   2   2
17  1   4   3
97  3   5   5
193 3   6   5
257 1   8   3
7681    15  9   17
12289   3   12  11
40961   5   13  3
65537   1   16  3
786433  3   18  10
5767169 11  19  3
7340033 7   20  3
23068673    11  21  3
104857601   25  22  3
167772161   5   25  3
469762049   7   26  3
1004535809  479 21  3
2013265921  15  27  31
2281701377  17  27  3
3221225473  3   30  5
75161927681 35  31  3
77309411329 9   33  7
206158430209    3   36  22
2061584302081   15  37  7
2748779069441   5   39  3
6597069766657   3   41  5
39582418599937  9   42  5
79164837199873  9   43  5
263882790666241 15  44  7
1231453023109121    35  45  3
1337006139375617    19  46  3
3799912185593857    27  47  5
4222124650659841    15  48  19
7881299347898369    7   50  6
31525197391593473   7   52  3
180143985094819841  5   55  6
1945555039024054273 27  56  5
4179340454199820289 29  57  3
```

