#include <bits/stdc++.h>

#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl

using namespace std;

const int MAXN=2505,MODE=1e9+7;
struct Str
{
    int l[MAXN],r[MAXN];
    int top;
} s[2];
int dp[MAXN][MAXN];

void read(Str* s)
{
    char c;
    int top=1;
    s->l[0]=s->r[0]=0;
    while(c=getchar())
    {
        if(c=='(')
        {
            s->l[top]=s->l[top-1]+1;
            s->r[top]=s->r[top-1];
            ++top;
        } else if(c==')')
        {
            s->l[top]=s->l[top-1];
            s->r[top]=s->r[top-1]+1;
            ++top;
        }
        else break;
    }
    s->top=top-1;
}

int main()
{
    scanf("\n");
    read(&s[0]);
    scanf("\n");
    read(&s[1]);
    int l1=s[0].top,l2=s[1].top;
    if(s[0].l[l1]+s[1].l[l2]!=s[0].r[l1]+s[1].r[l2])
    {
        printf("0\n");
    } else
    {
        dp[0][0]=0;
        for(int i=1;i<=l1;++i)
        {
            if(s[0].l[i]>=s[0].r[i]) dp[i][0]=1;
            else break;
        }
        for(int i=1;i<=l2;++i)
        {
            if(s[1].l[i]>=s[1].r[i]) dp[0][i]=1;
            else break;
        }
        for(int L=1;L<=l1+l2;++L)
        {
            for(int i=max(1,L-l2);i<L&&i<=l1;++i)
            {
                if(s[0].l[i]+s[1].l[L-i]>=s[0].r[i]+s[1].r[L-i])
                {
                    dp[i][L-i]=dp[i-1][L-i]+dp[i][L-i-1];
                    if(dp[i][L-i]>MODE) dp[i][L-i]%=MODE;
                } else dp[i][L-i]=0;
            }
        }
        printf("%d\n",dp[l1][l2]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-08 10:39:03 NK21652
类似于括号匹配,dp[i][j]表示串1匹配到i位串2匹配到j位的方法数
==================================================================*/