#include <bits/stdc++.h>
//杜教筛模板题
using namespace std;

typedef long long ll;
const int sz = 1664520;
int mu[sz], pri[130000], num_pri = 0;
map<int, ll> m;

void init()
{
    fill(mu, mu + sz, 2);
    mu[0] = 0, mu[1] = 1;
    for(int i = 2; i < sz; i++)
    {
        if(mu[i] == 2) mu[i] = -1, pri[num_pri++] = i;
        for(int j = 0; j < num_pri && i * pri[j] < sz; j++)
        {
            if(i % pri[j])
                mu[i * pri[j]] = mu[i] * -1;
            else
            {
                mu[i * pri[j]] = 0;
                break;
            }
        }
    }
    for(int i = 2; i < sz; i++) mu[i] += mu[i - 1];
    return;
}

int sum_mu(int x)
{
    if(x < sz) return mu[x];
    if(m.count(x)) return m[x];
    int ans = 1;
    for(int i = 2, j; i <= x; i = j + 1)
    {
        j = x / (x / i);
        ans -= (j - i + 1) * sum_mu(x / i);
    }
    return m[x] = ans;
}

ll sum_phi(int x)
{
    ll ans = 0;
    for(int i = 1, j; i <= x; i = j + 1)
    {
        j = x / (x / i);
        ans += 1ll * (x / i) * (x / i) * (sum_mu(j) - sum_mu(i - 1));
    }
    return ((ans - 1) >> 1) + 1;
}

int main()
{
    init();
    int cas,n;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &n);
        printf("%lld %d\n", sum_phi(n), sum_mu(n));
    }
    return 0;
}

/*=======================================
added at 2018年9月12日 14:24:06	problem:P4213
莫比乌斯反演、杜教筛
然后用数论分块和map记录优化时间
sum_phi的公式还要自己再推一遍
=======================================*/