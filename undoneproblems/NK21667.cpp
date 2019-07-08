#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=25;
char land[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN][3];
pii pos[MAXN*MAXN];
int win[MAXN],top;

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%s",land[i]);
        for(int j=0;j<n;++j)
        {
            if(land[i][j]=='W') ++win[i];
            else if(i>j&&land[i][j]=='?') pos[top++]=pii(i,j);
        }
    }
    for(int i=0;i<)
    return 0;
}

/*==================================================================
added at 2019-07-07 14:43:53 NK21667
设f为所有队伍赢的场次二阶矩
dp[i][j][w1][w2][s]表示填第k个空格(i,j),i已经赢了w1场,j已经赢了w2场时s=
0. 该位置填?时的f
1. 该位置填W时的f
2. 该位置填L时的f
转移方程:
dp[i][j][w1][w2][1]=dp[i][j][w1-1][w2][0]+2*w1-1
dp[i][j][w1][w2][2]=dp[i][j][w1][w2-1][0]+2*w2-1
dp[i][j][w1][w2][0]=max(dp[k+1][])
==================================================================*/