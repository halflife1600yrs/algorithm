#include <bits/stdc++.h>

using namespace std;

const int MODE=1e9+7;
typedef long long ll;

ll inv(int x)
{
    ll ans=1,base=x,up=MODE-2;
    while(up)
    {
        if(up&1) ans=ans*base%MODE;
        base=base*base%MODE;
        up>>=1;
    }
    return ans;
}

int main()
{
    int T,n,m;
    ll ans=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        if(n==1&&m==0) printf("%lld\n",ans);
        else if(m==0) ans=0,printf("0\n");
        else ans=(ans*inv(n-1))%MODE,printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-23 17:35:13	NK882A

==================================================================*/