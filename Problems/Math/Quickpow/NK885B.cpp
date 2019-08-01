
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
unsigned int mode;
const int MAXN = 1e6 + 5;

struct matrix
{
    ll a, b, c, d;
    matrix(ll _a = 0, ll _b = 0, ll _c = 0, ll _d = 0)
        : a(_a), b(_b), c(_c), d(_d) {}
    matrix& operator*=(const matrix& rhs)
    {
        return (*this) = matrix(
                   (a * rhs.a + b * rhs.c) % mode,
                   (a * rhs.b + b * rhs.d) % mode,
                   (c * rhs.a + d * rhs.c) % mode,
                   (c * rhs.b + d * rhs.d) % mode);
    }

    matrix operator*(const matrix& rhs) const
    {
        return matrix(
            (a * rhs.a + b * rhs.c) % mode,
            (a * rhs.b + b * rhs.d) % mode,
            (c * rhs.a + d * rhs.c) % mode,
            (c * rhs.b + d * rhs.d) % mode);
    }
};

inline matrix pow2(const matrix& x)
{
    return matrix(
        (x.a * x.a + x.b * x.c) % mode,
        (x.a * x.b + x.b * x.d) % mode,
        (x.c * x.a + x.d * x.c) % mode,
        (x.c * x.b + x.d * x.d) % mode);
}

inline matrix pow4(const matrix& x)
{
    return pow2(pow2(x));
}

inline matrix pow8(const matrix& x)
{
    return pow2(pow4(x));
}

char num[MAXN];
int L;

matrix quick_pow(matrix a)
{
    matrix ans(1, 0, 0, 1);
    while(L)
    {
        switch(num[L - 1] - '0')
        {
        case 1: ans *= a; break;
        case 2: ans *= pow2(a); break;
        case 3: ans *= a * pow2(a); break;
        case 4: ans *= pow4(a); break;
        case 5: ans *= a * pow4(a); break;
        case 6: ans *= pow2(a) * pow4(a); break;
        case 7: ans *= a * pow2(a) * pow4(a); break;
        case 8: ans *= pow8(a); break;
        case 9: ans *= a * pow8(a); break;
        }
        a *= (a * pow8(a));
        --L;
    }
    return ans;
}

int main()
{
    int x0, x1, a, b, n;
    scanf("%d %d %d %d", &x0, &x1, &a, &b);
    scanf("%s %u", num, &mode);
    L = strlen(num);
    if(L == 1 && num[0] == '1')
    {
        printf("%d\n", x1);
        return 0;
    }
    matrix x = matrix(a, b, 1, 0);
    matrix ans = quick_pow(x);
    printf("%llu\n", (ans.c * x1 + ans.d * x0) % mode);
    return 0;
}

/*==================================================================
added at 2019-08-01 14:06:53 2019牛客多校第五场B
以10为底的快速幂
==================================================================*/