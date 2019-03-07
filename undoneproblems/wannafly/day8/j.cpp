#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mode=998244353;

bool read()
{
    char c;
    while(c=getchar())
    {
        if(c==' '||c=='\n') continue;
        if(c=='1') return 1;
        if(c=='0') return 0;
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    ll ans=0;
    for(ll i=0;i<n;++i) //注意这里的ll
        for(ll j=0;j<m;++j)
            if(read())
                ans=(ans+((i+1)*(n-i)%mode)*((j+1)*(m-j)%mode)%mode)%mode;
    printf("%lld",ans);
    return 0;
}