#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
ll inv6, inv2;

ll inv(int x)
{
    ll ans = 1, base = x, ind = mod - 2;
    while(ind)
    {
        if(ind & 1) ans = ans * base % mod;
        base = base * base % mod, ind >>= 1;
    }
    return ans;
}

ll sum_k(int x) { return inv2 * x % mod * (x + 1) % mod; }
ll sum_square(int x) { return inv6 * x % mod * (x + 1) % mod * (2 * x + 1) % mod; }
ll sum_cube(int x) { return sum_k(x) * sum_k(x) % mod; }

ll f(int x) { return (sum_square(x) + sum_k(x)) * inv2 % mod; }
ll f_even(int x) { return (2 * sum_square(x) + sum_k(x)) % mod; }
ll f_odd(int x) { return (f(2 * x + 1) - f_even(x) + mod) % mod; }

ll sum_f(int x) { return (sum_cube(x) + 3 * sum_square(x) + 2*sum_k(x)) % mod * inv6 % mod; }
ll sum_f_even(int x) { return (8 * sum_cube(x) + 12 * sum_square(x) + 4 * sum_k(x)) % mod * inv6 % mod; }
//2+4+..+2x
ll sum_f_odd(int x) { return (sum_f(2 * x + 1) - sum_f_even(x) + mod) % mod; }
//1+3+..+(2x+1)

int main()
{
    inv6 = inv(6), inv2 = inv(2);
    int cas, n;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &n);
        ll ans;
        if((n - 1) & 1)
        {
            ans = f(n) + 2 * sum_f_odd(n / 2 - 1) - f_odd(n / 2 - 1);
        } else
        {
            ans = f(n) + 2 * sum_f_even((n - 1) / 2) - f_even((n - 1) / 2);
        }
        printf("%I64d\n", (ans % mod + mod) % mod);
    }
    return 0;
}

/*=======================================
added at 2018年11月18日 15:41:06	problem:NanjinH
一个六边形可以产生2个合法三角形，枚举六边形的水平边和60度边的长度
单个的三角形可以看成3条边长度为0其只能生成一个合法三角形的"六边形"
设f(x)=\sum_{i=1}^n i(i+1)/2
x=0时,y可以取1,2,..,n,对每一个y,可以在金字塔中找到1+2+..+(n+1-y)个这样的"六边形"
即x=0时,"六边形"个数为f(1)+f(2)+..+f(n)
x=1时,y最大可以取到n-1;x每+1,y能取到的最大值就-2
即总共的"六边形"个数为f(n)+[f(n-1)+f(n-3)+f(n-5)+...]
但是有的"六边形"是三条边长度为0的三角形,所以全部*2之后要减掉多算的那些
即答案=f(n)+2*[f(n-1)+f(n-3)+...]-(1+..+n-1)-(1+..+n-3)-...
分奇偶讨论即可
=======================================*/