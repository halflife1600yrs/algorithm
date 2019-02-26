#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e3+5,mode=998244353;
int num[MAXN];

ll diff_pos(int a,int b)
{
    ll pos=0;
    for(ll i=1,j=0;i<=max(a,b);i<<=1,++j)
    {
        if((a&i)!=(b&i)) pos=j;
    }
    return pos;
}

int search(int m,int pos,bool digit)
{
    int front=m>>(pos+1),after=m&((1<<pos)-1);
    bool mid=m&(1<<pos)?1:0;
    int ans=front*(1<<pos);
    if(mid==digit) ans+=after+1;
    else if(mid>digit) ans+=(1<<pos);
    return ans;
}

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=0;i<n;++i) scanf("%d",&num[i]);
        ll pos;
        bool need;
        ll ans=0;
        for(int i=0;i<n-1;++i)
            for(int j=i+1;j<n;++j)
            {
                if(num[i]>num[j]) ans=(ans-1+mode)%mode;
                pos=diff_pos(num[i],num[j]);
                need=num[i]&(1<<pos)?0:1;
                ans=(ans+search(m,pos,need))%mode;
            }
        printf("%lld\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Feb26 21:45:33	problem:f
对每对数判断异或几个数可以产生逆序对
=======================================*/