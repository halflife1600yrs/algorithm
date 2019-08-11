#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int val[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    ll sum=0;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&val[i]);
        sum+=val[i];
    }
    sort(val,val+n);
    ll ans=0;
    for(int i=0;i<n;++i)
    {
        ans+=sum*val[i]+(sum-val[i])*val[i];
        sum-=val[i];
    }
    printf("%lld\n",ans);
    return 0;
}