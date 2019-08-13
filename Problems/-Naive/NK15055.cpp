#include <bits/stdc++.h>

typedef long long ll;

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        ll ans=0,i=1;
        while((n&1)&&(m&1))
        {
            ans+=i;
            i*=4;
            n=(n-1)>>1;
            m=(m-1)>>1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}