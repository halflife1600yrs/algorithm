#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll quick_pow(int base,int expo,int mode)
{
    ll ans=1,tmp=base;
    while(expo)
    {
        if(expo&1) ans=ans*tmp%mode;
        tmp=tmp*tmp%mode;
        expo>>=1;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n,k1,k2;
        scanf("%d%d%d%d",&m,&n,&k1,&k2); // m/n
        ll power=quick_pow(10,k1-1,n);
        for(int i=k1;i<=k2;++i)
        {
            printf("%lld",power*m%n*10/n);
            power=power*10%n;
        }
        printf("\n");
    }
    return 0;
}