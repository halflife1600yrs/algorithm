#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[70], dp2[70];
ll n, d;
ll get_dp(int x)
{
    if(x < 0)
        return 0;
    else
        return dp[x];
}
ll get_ans(int x) //高度为x的平衡树不平衡度
{
    if(x <= d) return 0;
    for(ll i = d + 1; i < n - d; i++)
        if(get_dp(i - d - 1))
            dp2[i] = 0;
        else
            dp2[i] = get_dp(i - 1) - get_dp(i - d - 1);
    for(ll i = d + 2; i < n; i++)
        dp2[i] += dp2[i - 1];
    return dp2[x];
}
int main()
{
    while(~scanf("%lld %lld", &n, &d))
    {
        for(int i = 0; i <= d + 1; i++) dp[i] = i;
        for(int i = d + 2; i <= n - d - 1; i++) dp[i] = dp[i - 1] + dp[i - 1 - d] + 1;
        ll tmp = get_ans(n - d - 2);
        printf("%lld\n", (1 << (n - 1)) - 1 - get_dp(n - d - 1) + tmp);
    }
    return 0;
}