#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXP=205,MAXN=2e7+5,MODE=20170408;
int n,m,p;

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

typedef vector<int> poly;
poly polymul(const poly& x,const poly& y)
{
    poly ans(x.size()+y.size()-1,0);
    for(int i=0;i<x.size();++i)
        for(int j=0;j<y.size();++j)
            ans[i+j]=add(ans[i+j],x[i]*1ll*y[j]%MODE);
    for(int i=p;i<ans.size();++i) ans[i-p]=add(ans[i-p],ans[i]);
    ans.resize(p);
    return ans;
}

poly polypow(const poly& x,int index)
{
    poly ans(1,1),base=x;
    while(index)
    {
        if(index&1) ans=polymul(ans,base);
        base=polymul(base,base);
        index>>=1;
    }
    return ans;
}

bool sieve[MAXN]; // 线性筛质数
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
}

int main()
{
    init();
    scanf("%d %d %d",&n,&m,&p);
    poly p1(p,0),p2(p,0);
    for(int i=1;i<=m;++i)
    {
        ++p1[i%p];
        if(i==1||sieve[i]) ++p2[i%p];
    }
    poly ans1=polypow(p1,n);
    poly ans2=polypow(p2,n);
    int ans=(ans1[0]-ans2[0])%MODE;
    if(ans<0) ans+=MODE;
    printf("%d\n",ans);
}

/*==================================================================
added at 2019-08-03 21:44:43 P3702
朴素的多项式乘法,居然因为爆下标WA了一个小时
1000000000 97 97
==================================================================*/