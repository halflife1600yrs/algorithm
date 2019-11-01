#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll mode;
int sieve[1005], pri[200], num_pri = 0, sq;
typedef struct Irra
{
    ll rat, ira;
    Irra(ll r, ll i)
        : rat(r % mode), ira(i % mode){};
    Irra operator * (Irra &a)
    {
        return Irra(rat * a.rat % mode + (sq * ira % mode) * a.ira % mode, rat * a.ira % mode + ira * a.rat % mode);
    }
}Irra;

int resolve()   //分解所有完全平方因子
{
    int integer = 1, i = 0;
    while(i < num_pri && pri[i] * pri[i] <= sq)
    {
        if(sq%(pri[i]*pri[i])==0)
            sq /= pri[i] * pri[i], integer *= pri[i];
        else
            i++;
    }
    return integer;
}

Irra QuickPow(Irra base,ll powr)
{
    Irra ans(1, 0);
    while(powr)
    {
        if(powr & 1) ans = ans * base;
        base = base * base;
        powr >>= 1;
    }
    return ans;
}

int main()
{
    for(int i = 2; i < 1005; i++) //筛质数
    {
        if(!sieve[i]) pri[num_pri++] = i;
        for(int j = 0; j < num_pri && i * pri[j] < 1005; j++)
        {
            sieve[i * pri[j]] = 1;
            if(pri[j] % i == 0) break;
        }
    }
    int cas;
    scanf("%d", &cas);
    ll a, n;
    while(cas--)
    {
        scanf("%lld%d%lld%lld", &a, &sq, &n, &mode);
        Irra ans = QuickPow(Irra(a, resolve()), n);
        printf("1 %lld %d\n", ans.ira, sq);
    }
    return 0;
}

/*=======================================
added at 2018年9月16日 00:30:50	problem:HDU6442
鬼知道我为什么要搞这么晚、、、
需要重新考虑先取模再除和先除再取模的问题
=======================================*/
/*=======================================
added at 2018年9月16日 08:43:34	problem:HDU6442
分解没写对
bi不需要取模.....
然后确实不需要算两个减一下除2，第一个的系数和第二个的系数是相反数
原来这样写也行：
printf("1 %lld %d\n", QuickPow(Irra(a, resolve()), n).ira, sq);
=======================================*/