#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,ll> pil;
int a[55];
ll num[55];
pil b[55];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&a[i]);
    sort(a,a+n,greater<int>());
    scanf("%d",&m);
    for(int i=0;i<m;++i)
        scanf("%d",&b[i].first);
    for(int i=0;i<m;++i)
        scanf("%lld",&b[i].second);
    for(int i=0;i<m;++i)
        for(int j=0;j<=n;++j)
            if(a[j]<b[i].first) num[j]+=b[i].second;
    if(num[0])
    {
        puts("-1");
        return 0;
    }
    for(int i=0;i<n;++i) num[i]=num[i+1]-num[i];
    for(int i=1;i<n;++i) num[i]+=num[i-1];
    ll maxi=0;
    for(int i=0;i<n;++i)
        maxi=max(maxi,(ll)ceil(1.0*num[i]/(i+1)));
    printf("%lld\n",maxi);
    return 0;
}