#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int sz = 1000;
ll dp[200005];
ll C[sz][sz];

#define DEBUG
#define debug1(x) cout<<#x" = "<<x<<endl;
#define debug2(x,y) cout<<#x" = "<<x<<" ,"#y" = "<<y<<endl;

ll inv(ll x, ll k)
{
    ll ans = 1, tmp = x, powr = k - 2;
    while(powr)
    {
        if(powr & 1) ans = ans * tmp % k;
        tmp = tmp * tmp % k;
        powr >>= 1;
    }
    return ans;
}

ll get_C(int n, int m, int p)
{
    // debug2(n, m);
    if(n > m) return 0;
    if(n == 0 || n == m) return 1 % p;
    if(n == 1 || m - n == 1) return m % p;
    ll ans;
    if(n < sz && m < sz)
    {
        if(C[n][m]) return C[n][m];
        if(C[m - n][m]) return C[m - n][m];
        ans = dp[m] * inv(dp[n] * dp[m - n] % p, p) % p;
        C[n][m] = ans;
    } else
        ans = dp[m] * inv(dp[n] * dp[m - n] % p, p) % p;
    return ans;
}

ll Lucas(int n, int m, int p) //求c(n,m) mod p
{
    // debug2(n, m);
    if(n == 0) return 1;
    if(n == 1) return m % p;
    ll ans = get_C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
    return ans;
}

int main()
{
    int cas, n, m, p;
    scanf("%d", &cas);
    while(cas--)
    {
        memset(C, 0, sizeof(C));
        scanf("%d %d %d", &n, &m, &p);
        if(p == 1)
        {
            printf("0\n");
            continue;
        }
        dp[0] = 1;
        for(ll i = 1; i <= n + m; i++)
            dp[i] = i * dp[i - 1] % p;
        printf("%lld\n", Lucas(m, n + m, p));
    }
    return 0;
}

/*=======================================
added at 2018年9月21日 20:01:04	problem:P3807

=======================================*/