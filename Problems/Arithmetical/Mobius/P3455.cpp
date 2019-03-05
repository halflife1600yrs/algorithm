#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=5e4+5;
bool unpri[MAXN];
int mu[MAXN],sum_mu[MAXN];
struct Quee
{
    int data[MAXN],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} pri;

void seive()
{
    pri.top=0;
    mu[1]=1,sum_mu[1]=1;
    for(int i=2;i<MAXN;++i)
    {
        if(!unpri[i])
        {
            pri.add(i);
            mu[i]=-1;
        }
        for(int j=0,k=i*pri[0];k<MAXN&&j<pri.top;++j,k=i*pri[j])
        {
            unpri[k]=1;
            if(i%pri[j]==0)
            {
                mu[k]=0;
                break;
            } else
            {
                mu[k]=-1*mu[i];
            }
        }
        sum_mu[i]=sum_mu[i-1]+mu[i];
    }
}

ll gcd1(int n,int m)
{
    ll ans=0;
    for(int i=1,j;i<=n;i=j+1)
    {
        j=min(n/(n/i),m/(m/i));
        ans+=1ll*(sum_mu[j]-sum_mu[i-1])*(m/i)*(n/i);
    }
    return ans;
}

int main()
{
    seive();
    int T,n,m,a;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&m,&a);
        if(n>m) swap(n,m);
        ll ans=gcd1(n/a,m/a);
        printf("%lld\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Mar01 13:50:02	problem:P3455
求i小于n，j小于m，gcd(i,j)=1的对数
模板题
=======================================*/