#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll lowbit(ll x)
{
    return x&(-x);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        if(!(a&b)) printf("%lld\n",min(lowbit(a),lowbit(b)));
        else printf("%lld\n",a&b);
    }
    return 0;
}

/*==================================================================
added at 2019-08-23 19:26:30 2019CCPC网络赛1001
贪心
注意题目要求答案大于0
==================================================================*/