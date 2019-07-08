#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=105;
char s1[MAXN],s2[MAXN];
bool dp[MAXN][MAXN][MAXN];

int main()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    int l1=strlen(s1+1),l2=strlen(s2+1);
    dp[0][0][0]=1;
    for(int j=0;j<l2;++j)
    {
        for(int i=j;i<=l1;++i)
        {
            for(int k=i-j;k>=0;k-=2)
            {
                if(dp[i][j][k])
                {
                    if(s1[i+1]==s2[j+1]&&!k) dp[i+1][j+1][0]=1;
                    if(s1[i+1]==')'&&k>0) dp[i+1][j][k-1]=1;
                    else if(s1[i+1]=='(') dp[i+1][j][k+1]=1;
                }
            }
        }
    }
    printf("%s\n",dp[l1][l2][0]?"Possible":"Impossible");
    return 0;
}

/*==================================================================
added at 2019-07-08 10:40:59 NK21303
类似于括号匹配,但是可以多次删除连续的()
dp[i][j][k]表示串1匹配到i串2匹配到j前面已经删除的'('比')'多k个
==================================================================*/