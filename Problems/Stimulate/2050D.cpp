#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll cal(int num,int c2,int c3)
{
    if(!num) return 0;
    if(num<=2) return min(c2,c3);
    double v2=c2/2.0,v3=c3/3.0;
    if(v2<v3)
    {
        double rooms=num/2.0;
        if(num&1) return min(ceil(rooms)*c2,(floor(rooms)-1)*c2+c3);
        return 1ll*(num>>1)*c2;
    } else
    {
        if(num%3==0) return 1ll*num/3ll*c3;
        double rooms=num/3.0;
        if(num%3==2) return min(ceil(rooms)*c3,floor(rooms)*c3+c2);
        return min(ceil(rooms)*c3,(floor(rooms)-1)*c3+2ll*c2);
    }
}

int main()
{
    int T;
    int n,m,k,a,b,c;
    // while(~scanf("%d %d %d",&n,&a,&b)) cout<<cal(n,a,b)<<endl;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&m,&k);
        scanf("%d %d %d",&a,&b,&c);
        ll ans,mini=0x7f7f7f7f7f7f7f7f;
        for(int i=0;i<=k;++i)
        {
            ans=1ll*i*c;
            ans+=cal(n+k-i,a,b);
            ans+=cal(m+k-i,a,b);
            if(ans<mini) mini=ans;
        }
        printf("%lld\n",mini);
    }
    return 0;
}