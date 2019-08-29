#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int t,T,x,cost;
    ll ans=0;
    for(int i=0;i<n;++i)
    {
        scanf("%d %d %d %d",&t,&T,&x,&cost);
        if(T-t>=m) ans+=cost;
        else if(T<=t) ans+=cost+m*(ll)x;
        else ans+=min(cost+m*(ll)x,(m+T-t-1)/(T-t)*(ll)cost);
    }
    printf("%I64d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-27 09:53:07 CF215D
费用关于两种价格呈线性，所以一定是按更优的策略做到底
==================================================================*/