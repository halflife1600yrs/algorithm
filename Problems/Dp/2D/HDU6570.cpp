#include<bits/stdc++.h>

using namespace std;
const int MAXN=1e5+5;
typedef long long ll;
int n,c;
int a[MAXN],dp[105][105];

int main()
{
    while (~scanf("%d %d",&n,&c))
    { 
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;i++)
        {
            int x=a[i];
            for(int j=1;j<=c;j++)
                if(j!=x && dp[x][j]%2==0)
                    dp[x][j]++;
            for(int j=1;j<=c;j++)
                if(j!=x && dp[j][x]%2==1)
                    dp[j][x]++;
        }
        int ans=0;
        for(int i=1;i<=c;i++)
            for(int j=1;j<=c;j++)
                if(i!=j && dp[i][j]>ans && dp[i][j]>1)
                    ans=dp[i][j];
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-11 19:36:54 HDU6570
dp[i][j]表示奇位为i,偶位为j的最长序列的长度
==================================================================*/