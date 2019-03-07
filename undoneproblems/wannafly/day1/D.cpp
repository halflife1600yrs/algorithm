#include <bits/stdc++.h>

int data[15][15];
int dp[2][15][15];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n, m, c;
    int xs, ys, xt, yt;
    while(~scanf("%d %d %d", &n, &m, &c))
    {
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                scanf("%d", &data[i][j]);
        scanf("%d%d%d%d", &xs, &ys, &xt, &yt);
        memset(dp, 0, sizeof(dp));
        int t = 1;
        bool pos = 1;
        while(dp[!pos][xt][yt] < c)
        {
            for(int i = 1; i <= n; ++i)
            {
                for(int j = 1; j <= m; ++j)
                {
                    if(t < abs(i - xs) + abs(j - ys)) continue;
                    bool plus = t % data[i][j] == 0;
                    if(plus)
                        dp[pos][i][j] = dp[!pos][i][j] + 1;
                    else
                        dp[pos][i][j] = dp[!pos][i][j];
                    if(j > 1 && t >= abs(i - xs) + abs(j - 1 - ys))
                    {
                        if(plus)
                        {
                            if(dp[!pos][i][j - 1] + 1 > dp[pos][i][j])
                                dp[pos][i][j] = dp[!pos][i][j - 1] + 1;
                        } else if(dp[!pos][i][j - 1] > dp[pos][i][j])
                            dp[pos][i][j] = dp[!pos][i][j - 1];
                        // printf("[<%d]", dp[!pos][i][j - 1]);
                    }
                    if(j < m && t >= abs(i - xs) + abs(j + 1 - ys))
                    {
                        if(plus)
                        {
                            if(dp[!pos][i][j + 1] + 1 > dp[pos][i][j])
                                dp[pos][i][j] = dp[!pos][i][j + 1] + 1;
                        } else if(dp[!pos][i][j + 1] > dp[pos][i][j])
                            dp[pos][i][j] = dp[!pos][i][j + 1];
                        // printf("[>%d]", dp[!pos][i][j + 1]);
                    }
                    if(i > 1 && t >= abs(i - 1 - xs) + abs(j - ys))
                    {
                        if(plus)
                        {
                            if(dp[!pos][i - 1][j] + 1 > dp[pos][i][j])
                                dp[pos][i][j] = dp[!pos][i - 1][j] + 1;
                        } else if(dp[!pos][i - 1][j] > dp[pos][i][j])
                            dp[pos][i][j] = dp[!pos][i - 1][j];
                        // printf("[^%d]", dp[!pos][i - 1][j]);
                    }
                    if(i < n && t >= abs(i + 1 - xs) + abs(j - ys))
                    {
                        if(plus)
                        {
                            if(dp[!pos][i + 1][j] + 1 > dp[pos][i][j])
                                dp[pos][i][j] = dp[!pos][i + 1][j] + 1;
                        } else if(dp[!pos][i + 1][j] > dp[pos][i][j])
                            dp[pos][i][j] = dp[!pos][i + 1][j];
                        // printf("[<%d]", dp[!pos][i + 1][j]);
                    }
                    // printf("%d(%d) ", dp[pos][i][j], dp[!pos][i][j]);
                }
                // printf("\n");
            }
            // printf("\n");
            ++t, pos = !pos;
        }
        printf("%d\n", t - 1);
    }
    return 0;
}