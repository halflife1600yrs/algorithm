#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=2e5+5,MODE=1e9+7;
map<ll,ll> invs;
typedef pair<ll,double> pld;
pld val[MAXN];

inline bool cmp(const pld& a,const pld& b) { return a.second>b.second; }

inline void mul(ll& x,ll y)
{
    x*=y;
    if(x>MODE) x%=MODE;
}

inline ll inv(int base)
{
    ll ans=1,tmp=base;
    int up=MODE-2;
    while(up)
    {
        if(up&1) mul(ans,tmp);
        mul(tmp,tmp);
        up>>=1;
    }
    return ans;
}

inline ll get_inv(ll x)
{
    if(invs.count(x))
        return invs[x];
    else
    {
        ll ans=inv(x);
        invs[x]=ans;
        return ans;
    }
}

int main()
{
    int n;
    ll v,e;
    int top=0;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%lld %lld",&v,&e);
        val[top].second=1.0*e/v;
        mul(e,get_inv(v));
        val[top].first=e;
        top++;
    }
    sort(val,val+n,cmp);
    for(int i=0;i<n;++i)
        printf("%lld\n",val[i].first);
    return 0;
}