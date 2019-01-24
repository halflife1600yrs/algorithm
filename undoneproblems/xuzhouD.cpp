#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int sz = 16e5;
int mu[sz], pri[122000], num_pri = 0;

void init()
{
    fill(mu, mu + sz, 2);
    for(int i = 2; i < sz; i++)
    {
        if(mu[i] == 2) mu[i] = -1, pri[num_pri++] = i;
        for(int j = 0; j < num_pri && i * pri[j] < sz; j++)
        {
            if(i % pri[j])
                mu[i * pri[j]] = -1 * mu[i];
            else
            {
                mu[i * pri[j]] = 0;
                break;
            }
        }
    }
    for(int i = 2; i < sz; i++) mu[i] += mu[i - 1];
}

ll sum_mu(ll x)
{
    if()
}

ll get_sum(ll x)
{

}

int main()
{
    init();
    ll n, m;
    while(~scanf("%lld %lld",&n,&m))
    {
        ll tmp = n;
        int mun = 1, k = 0;
        while(n > 1)
        {
            if(n % (pri[k]*pri[k]) == 0)
            {
                mun = 0;
                break;
            }
            else if(n%pri[k]==0)
            {
                mun *= -1;
                n /= pri[k++];
            }
            else if()
        }
    }
    return 0;
}

/*=======================================
added at 2018年9月12日 23:27:47	problem:xuzhoud
筛法相关
=======================================*/