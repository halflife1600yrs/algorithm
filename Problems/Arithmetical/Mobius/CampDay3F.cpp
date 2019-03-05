#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e7+5;
const int MODE=998244353;
struct
{
    int data[700000],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} pri;
bool notpri[MAXN];
int mu[MAXN];
int sum_mu[MAXN];

void sieve()
{
    mu[1]=1,sum_mu[1]=1,sum_mu[0]=0;
    int maxi=pri.top=0;
    for(int i=2;i<MAXN;++i)
    {
        if(!notpri[i]) pri.add(i),mu[i]=-1;
        for(int j=0,k=2*i;j<pri.top&&i*pri[j]<MAXN;++j,k=i*pri[j])
        {
            notpri[k]=1;
            if(i%pri[j]==0)
            {
                mu[k]=0;
                break;
            }
            mu[k]=mu[i]*-1;
        }
        sum_mu[i]=sum_mu[i-1]+mu[i];
    }
}

ll G(ll n)
{
    ll ans=0;
    for(int i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans=(ans+(sum_mu[j]-sum_mu[i-1]+MODE)*((n/i)*(n/i)%MODE))%MODE;
    }
    return ans;
}

ll calcu(ll n)
{
    ll ans=0;
    for(int i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans=(ans+(sum_mu[j]-sum_mu[i-1]+MODE)*G(n/i))%MODE;
    }
    return ans;
}

int main()
{
    sieve();
    ll n;
    scanf("%lld",&n);
    printf("%lld\n",calcu(n));
    return 0;
}

/*=======================================
added at 2019.Mar05 19:59:03	problem:F
再次忘了取模为负的时候加上mode
=======================================*/