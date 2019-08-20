#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int MAXN=2e6+10,MODE=1e6+3;
ll multi[MAXN];
 
void init()
{
    multi[0]=multi[1]=1;
    for(int i=2;i<MAXN;++i)
        multi[i]=multi[i-1]*i%MODE;
}
 
ll inv(ll base)
{
    ll ans=1,ind=MODE-2;
    while(ind)
    {
        if(ind&1) (ans*=base)%=MODE;
        (base*=base)%=MODE;
        ind>>=1;
    }
    return ans;
}
 
inline ll C(int a,int b)
{ // choose b from a
    if(b>a) a+=MODE;
    return multi[a]*inv(multi[a-b])%MODE*inv(multi[b])%MODE;
}
 
inline ll lucas(int a,int b)
{
    return C(a/MODE,b/MODE)*C(a%MODE,b%MODE)%MODE;
}
 
int main()
{
    init();
    int T,n,a,b,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&a,&b);
        k=b-a;
        ll ans=lucas(n+k+1,k+1)-1;
        if(ans<0) ans+=MODE;
        printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-17 19:47:04 BZOJ4403
组合数公式+lucas定理
==================================================================*/