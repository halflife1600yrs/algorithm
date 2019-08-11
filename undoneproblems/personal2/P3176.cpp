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

typedef long long ll;
const int MAXN=505,MODE=998244353;
int m;

int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

struct mat
{
    int d[6][6];
    mat() { memset(d,0,sizeof(d)); }
    void setE()
    {
        memset(d,0,sizeof(d));
        for(int i=0;i<m;++i) d[i][i]=1;
    }
    int* operator[](int x)
    {
        return d[x];
    }
    const int* operator[](int x) const
    {
        return d[x];
    }
    mat& operator=(const mat& x)
    {
        for(int i=0;i<m;++i)
            for(int j=0;j<m;++j)
                d[i][j]=x[i][j];
        return *this;
    }
    mat operator*(const mat& x) const
    {
        mat ans;
        for(int i=0;i<m;++i)
            for(int j=0;j<m;++j)
                for(int k=0;k<m;++k)
                    ans[i][j]=add(ans[i][j],x[i][k]*(ll)d[k][j]%MODE);
        return ans;
    }
    mat operator+(const mat& x) const
    {
        mat ans;
        for(int i=0;i<m;++i)
            for(int j=0;j<m;++j)
                ans[i][j]=add(x[i][j],d[i][j]);
        return ans;
    }
    void print()
    {
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<m;++j) printf("%d ",d[i][j]);
            puts("");
        }
        puts("");
    }
};

mat pow10(const mat& x)
{
    mat m2=x*x,m4=m2*m2;
    return m2*m4*m4;
}

mat base,pows[10],dp[MAXN][MAXN],ans[MAXN];
int a[6];

void init()
{
    pows[0].setE();
    pows[1]=base;
    for(int i=2;i<10;++i) pows[i]=pows[i-1]*base,pows[i].print();
    a[0]=1;
    for(int i=1;i<m;++i)
        for(int j=0;j<i;++j) a[i]+=a[j];
    disp(a,0,m);
}

int main()
{
    char str[MAXN];
    scanf("%s",str);
    int n=strlen(str);
    scanf("%d",&m);
    for(int i=0;i<m;++i)
    {
        base[0][i]=1;
        if(i) base[i][i-1]=1;
    }
    init();
    for(int i=0;i<n;++i) dp[i][i]=pows[(int)(str[i]-'0')];
    for(int i=0;i<n-1;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            dp[i][j]=pow10(dp[i][j-1])*dp[j][j];
            debug2(i,j);
            dp[i][j].print();
        }
    }
    ans[0]=dp[0][0];
    for(int i=1;i<n;++i)
    {
        ans[i]=dp[0][i];
        for(int j=0;j<i;++j)
        {
            debug2(i,j);
            ans[j].print();
            dp[j+1][i].print();
            ans[i]=ans[i]+ans[j]*dp[j+1][i],ans[i].print();
        }
    }
    ll sum=0;
    for(int i=0;i<m;++i)
    {
        sum=add(sum,a[i]*(ll)ans[n-1][m-1][i]%MODE);
        debug2(a[i],ans[n-1][m-1][i]);
    }
    printf("%lld\n",sum);
    return 0;
}
/*==================================================================
added at 2019-08-06 22:07:02	P3176
3513541 5
==================================================================*/