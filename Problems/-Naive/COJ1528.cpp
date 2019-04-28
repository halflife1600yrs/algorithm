#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=200;
ll sum[MAXN];

int main()
{
    sum[1]=1,sum[2]=2;
    for(int i=3;i<MAXN;++i)
    {
        sum[i]=sum[i-1]/2;
        sum[i]+=sum[i-1];
    }
    ll x;
    scanf("%lld",&x);
    for(int i=1;i<MAXN;++i)
        if(sum[i]>x)
        {
            printf("%d\n",i);
            break;
        }
    return 0;
}