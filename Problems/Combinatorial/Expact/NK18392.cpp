#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7;
const ll i2=500000004,i3=333333336,i4=250000002;

inline ll mul(ll a,ll b)
{
    a*=b;
    if(a>MODE) a%=MODE;
    return a;
}

int main()
{
    int n;
    scanf("%d",&n);
    ll ans=mul(mul(n,2*n+3),i2)-mul(mul(n,2*n+1),i3)-n+mul(mul(n,n-1),i4);
    printf("%lld\n",(ans%MODE+MODE)%MODE);
    return 0;
}

/*==================================================================
added at 2019-07-09 17:47:13 NK18392
利用期望的加和性质,对每个数贡献的逆序对数期望加和
细分一下 偶数和偶数直接拿出来 奇数需要计算比它大的偶数在前/小的偶数在后
结论是n(2n+3)/2 - n(2n+1)/3 + n(n-1)/4 - n
==================================================================*/