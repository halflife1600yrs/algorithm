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
const int MAXP=205,MAXN=2e7+5,MODE=20170408;

int n,m,p;
int poly1[MAXP],poly2[MAXP],ans[MAXP],tmp[MAXP];

inline int add(int x,int y)
{
    return (x+y)%MODE;
}

void polymul(int* p1,int* p2)
{
    for(int i=0;i<2*p-1;++i)
    {
        tmp[i]=0;
        for(int j=0;j<p;++j)
        {
            if(i-j>=0&&i-j<p)
                tmp[i]=add(tmp[i],(p1[j]*(ll)p2[i-j])%MODE);
        }
    }
    for(int i=0;i<p;++i) p1[i]=add(tmp[i],tmp[i+p]);
}

void polypow(int* p1,int index)
{
    memset(ans,0,sizeof(ans));
    ans[0]=1;
    while(index)
    {
        if(index&1) polymul(ans,p1);
        polymul(p1,p1);
        index>>=1;
    }
}

bool sieve[MAXN];
int pri[1270610],pri_n;

void init()
{
    for(int i=2;i<MAXN;++i)
    {
        if(!sieve[i])  pri[pri_n++]=i;
        for(int j=0;j<pri_n&&i*pri[j]<MAXN;++j)
        {
            sieve[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
    // debug1(pri_n);
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    init();
    scanf("%d %d %d",&n,&m,&p);
    for(int i=0;i<p;++i) poly1[i]=poly2[i]=(m-i)/p+1;
    --poly1[0],--poly2[0];
    for(int i=0;i<pri_n&&pri[i]<=m;++i) --poly2[pri[i]%p];
    // disp(poly1,0,p)
    // disp(poly2,0,p)
    polypow(poly1,n);
    // disp(ans,0,p)
    int a1=ans[0];
    polypow(poly2,n);
    // disp(ans,0,p)
    a1=(a1-ans[0])%MODE;
    if(a1<0) a1+=MODE;
    printf("%d\n",a1);
    return 0;
}

/*==================================================================
added at 2019-08-03 21:44:43 P3702
朴素的多项式乘法,居然因为爆下标WA了一个小时
1000000000 97 97
==================================================================*/