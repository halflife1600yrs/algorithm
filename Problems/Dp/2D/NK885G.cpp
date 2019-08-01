#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int MAXN=3005,MODE=998244353;
int dp[2][MAXN],sum[MAXN];
char str1[MAXN],str2[MAXN];
int C[MAXN][MAXN];
 
inline int add(int a,int b)
{
    return (a+=b)>=MODE?a-MODE:a;
}
 
void pre()
{
    for(int i=C[0][0]=1;i<MAXN;++i)
        for(int j=C[0][i]=1;j<=i;++j) C[j][i]=add(C[j-1][i-1],C[j][i-1]);
    for(int i=1;i<MAXN;++i)
        for(int j=i-1;j>=0;--j) C[j][i]=add(C[j][i],C[j+1][i]); // 组合数后缀和
}
 
signed main()
{
    pre();
    int T, n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &n, &m);
        scanf("%s %s",str1,str2);
        int ans=0;
        for(int i=0;i<n;++i) // 预处理
            if(str1[i]==str2[0])
            {
                dp[0][i]=1;
                if(m==1&&i!=n-1)
                    ans=add(ans,C[1][n-i-1]);
            } else
            {
                if(n-i>=m)
                    if(str1[i]>str2[0])
                        ans=add(ans,C[m-1][n-i-1]);
                    else if(str1[i]!='0') // 前导0
                        ans=add(ans,C[m][n-i-1]);
                dp[0][i]=0;
            }
        bool pos=1;
        for(int i=1;i<m;++i)
        {
            sum[i-1]=dp[!pos][i-1];
            for(int j=i;j<n;++j) sum[j]=add(sum[j-1],dp[!pos][j]); // 求前缀和
            for(int j=i;j<n;++j)
                if(str1[j]==str2[i])
                {
                    dp[pos][j]=sum[j-1];
                    if(i==m-1&&j!=n-1)
                        ans=add(ans,(dp[pos][j]*(ll)C[1][n-j-1])%MODE); // 匹配完之后后面的那些数字可以任意选,但不能不选
                } else
                {
                    dp[pos][j]=0;
                    if(n-j>=m-i)
                        if(str1[j]>str2[i]) // 后面有足够的字符去匹配
                            ans=add(ans,sum[j-1]*(ll)C[m-i-1][n-j-1]%MODE); // 从后面的n-j-1个字符里面随便选m-i-1个,组合数后缀
                        else
                            ans=add(ans,sum[j-1]*(ll)C[m-i][n-j-1]%MODE); // 从后面的n-j-1个字符里面随便选m-i个一定要比它长
                }
            pos=!pos;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-01 20:35:05 2019牛客多校第五场G
初始化条件还是没有考虑好,没有考虑到第二个串只有1的情况
所以说测试的时候多造一点极限数据很有必要啊
==================================================================*/