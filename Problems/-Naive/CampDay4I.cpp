#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pLL;
const int MAXN=1005;
pLL card[MAXN];
ll num;

bool cmp(pLL a,pLL b)
{
    return a.second*num-a.first<b.second*num-b.first;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%lld%lld",&card[i].first,&card[i].second);
    ll sum,maxi=0;
    for(num=1;num<=n;++num)
    {
        sum=0;
        sort(card,card+n,cmp);
        int i=0;
        for(;i<num;++i) sum+=card[i].first;
        for(;i<n;++i) sum+=card[i].second*num;
        if(sum>maxi) maxi=sum;
    }
    printf("%lld\n",maxi);
    return 0;
}