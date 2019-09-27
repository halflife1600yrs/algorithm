#include <bits/stdc++.h>

using namespace std;

typedef int ll;
const int MAXN = 5e5 + 5;
int n, m, s[MAXN];
ll sum[MAXN], dp[MAXN];

int up(int k, int j)
{
    return dp[j] + sum[j] * sum[j] - (dp[k] + sum[k] * sum[k]);
}

int down(int k, int j)
{
    return 2 * (sum[j] - sum[k]);
}

int get(int i, int j)
{
    return dp[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + m;
}

int main()
{
    while(~scanf("%d %d", &n, &m))
    {
        sum[0] = 0;
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &sum[i]);
            sum[i] += sum[i - 1];
            dp[i] = 0;
        }
        int head = 0, tail = 1;
        dp[0] = s[0] = 0;
        for(int i = 1; i <= n; ++i)
        {
            while(head + 1 < tail && up(s[head], s[head + 1]) <= sum[i] * down(s[head], s[head + 1]))
                head++;
            dp[i] = get(i, s[head]);
            while(head + 1 < tail && up(s[tail - 2], s[tail - 1]) * down(s[tail - 1], i) >= up(s[tail - 1], i) * down(s[tail - 2], s[tail - 1]))
                tail--;
            s[tail++] = i;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}

/*==================================================================
added at 2019-09-19 20:04:33    HDU3507
5 100
49 1 1 1 1
斜率优化dp
又是打错了、、、
==================================================================*/