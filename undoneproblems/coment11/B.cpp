#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=1e3+5,INF=0x3f3f3f3f;
int n,m,k,val[MAXN];
int dp[2*MAXN];

inline int f(int x)
{
    return x>k?0:val[x];
}

int main()
{
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0;i<=k;++i) scanf("%d",&val[i]);
    memset(dp,0x3f,sizeof(dp));
    for(int i=dp[0]=0,a,b,c,d;i<m;++i)
    {
        scanf("%d %d",&a,&b);
        for(c=a,d=b;c<2*MAXN;c+=a,d+=b)
            dp[c]=min(dp[c],c-d);
    }
    for(int i=1;i<2*MAXN;++i)
        for(int j=0;2*j<=i;++j)
            dp[i]=min(dp[i],dp[j]+dp[i-j]);
    // disp(dp,0,50)
    int money=f(0),save=0;
    for(int i=2;i<=n;++i,money+=f(money))
    {
        int maxi=f(money),pos=0;
        for(int j=1;j<=money;++j)
        {
            if(f(money-j)-dp[j]>maxi)
            {
                maxi=f(money-j)-dp[j];
                pos=j;
            }
        }
        save+=pos-dp[pos];
        money-=pos;
    }
    printf("%d\n",money+save);
    return 0;
}

/*==================================================================
added at 2019-09-21 21:13:18 B
5 5 10
30 29 29 28 28 27 26 26 25 24 24
22 22
26 15
22 14
30 27
==================================================================*/