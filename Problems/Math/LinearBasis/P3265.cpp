#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int MAXN=505,MODE=1e9+7;
const double EPS=1e-8;

int n,m;
int equip[MAXN][MAXN];
pii cost[MAXN];

int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

ll inv(int x)
{
    ll ans=1,base=x,up=MODE-2;
    while(up)
    {
        if(up&1) (ans*=base)%=MODE;
        (base*=base)%=MODE;
        up>>=1;
    }
    return ans;
}

int b[MAXN][MAXN];

bool insert(int* x)
{
    ll k1,k2,g;
    for(int i=m-1;i>=0;--i)
    {
        if(x[i])
        {
            if(b[i][i])
            {
                g=inv(gcd(x[i],b[i][i]));
                k1=b[i][i]*g%MODE,k2=x[i]*g%MODE;
                for(int j=i;j>=0;--j)
                {
                    x[j]=(k1*x[j]-k2*b[i][j])%MODE;
                    if(x[j]<0) x[j]+=MODE;
                }
            } else
            {
                for(int j=i;j>=0;--j)
                    b[i][j]=x[j];
                return 1;
            }
        }
    }
    return 0;
}

bool cmp(const pii& a,const pii& b)
{
    return a.first<b.first;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            scanf("%d",&equip[i][j]);
    for(int i=0;i<n;++i)
        scanf("%d",&cost[i].first),cost[i].second=i;
    sort(cost,cost+n,cmp);
    int num=0,need=0;
    for(int i=0;i<n;++i)
    {
        if(insert(equip[cost[i].second]))
            ++num,need+=cost[i].first;
    }
    printf("%d %d\n",num,need);
    return 0;
}

/*==================================================================
added at 2019-08-05 20:12:09 P3265
本来要卡double精度的用ll和i128之后都过不了,看到一篇题解说用取模意义下的就过了
nb
==================================================================*/