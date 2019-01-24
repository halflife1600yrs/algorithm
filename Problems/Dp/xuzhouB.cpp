#include <bits/stdc++.h>
using namespace std;

int dp[1005][205];   //dp[i][j]表示倒数第i次操作时，分数为j，此时选的人能否赢，-1be，0ne，1ge
//boy先选，他想要分数高于R，girl后选，她想要分数小于L，两人不能达到目的时尽量不然对方赢
int n, m, R, L;     //n操作次数，m初始分数，L，R为范围

inline int vhash(int x)
{
    return x + 100;
}

int judge(int x)
{
    if(x<=L) return -1;
    else if(x>=R) return 1;
    else return 0;
}

int main()
{
    int a[1005], b[1005], c[1005];
    while(~scanf("%d%d%d%d",&n,&m,&R,&L))
    {
        for (int i = 0; i < n;i++)
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
        for (int i = -100; i <= 100; i++)
            dp[n][vhash(i)] = judge(i);
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = -100; j <= 100; j++)
            {
                if (i & 1)      //i为奇时女生选(0开始)
                {
                    int ans = 1;
                    if(a[i])
                    {
                        int g = vhash(min(j + a[i], 100));
                        ans = min(ans, dp[i + 1][g]);
                    }
                    if(b[i])
                    {
                        int g = vhash(max(j - b[i], -100));
                        ans = min(ans, dp[i + 1][g]);
                    }
                    if(c[i])
                    {
                        int g = vhash(-1 * j);
                        ans = min(ans, dp[i + 1][g]);
                    }
                    dp[i][vhash(j)] = ans;
                }
                else        //i为偶时男生选
                {
                    int ans = -1;
                    if(a[i])
                    {
                        int g = vhash(min(j + a[i], 100));
                        ans = max(ans, dp[i + 1][g]);
                    }
                    if(b[i])
                    {
                        int g = vhash(max(j - b[i], -100));
                        ans = max(ans, dp[i + 1][g]);
                    }
                    if(c[i])
                    {
                        int g = vhash(-1 * j);
                        ans = max(ans, dp[i + 1][g]);
                    }
                    dp[i][vhash(j)] = ans;
                }
            }
        }
        if(dp[0][vhash(m)]==1)
            printf("Good Ending\n");
        else if(dp[0][vhash(m)]==-1)
            printf("Bad Ending\n");
        else
            printf("Normal Ending\n");
    }
    return 0;
}