#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;

const int MAXN=2e5+5;
typedef pair<ll,ll> pll;
pll cre[MAXN];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n,a,b;
    while(~scanf("%d %d %d",&n,&a,&b))
    {
        // debug1(n);
        // debug2(a,b);
        ll sum=0;
        for(int i=0;i<n;++i)
        {
            scanf("%lld %lld",&cre[i].first,&cre[i].second);
            sum+=cre[i].second;
        }
        // debug1(sum);
        if(b==0)
        {
            printf("%lld\n",sum);
            continue;
        }
        sort(cre,cre+n,[](const pll& a,const pll& b){
            return a.first-a.second>b.first-b.second;
        });
        int pos=-1;
        if(a)
        {
            ll maxi=0,multi=1ll<<a;
            // debug1(multi);
            for(int i=0;i<n;++i)
            {
                if(multi*cre[i].first-cre[i].second>maxi)
                {
                    maxi=multi*cre[i].first-cre[i].second;
                    pos=i;
                }
            }
            // debug1(maxi);
            if(maxi>0)
            {
                sum+=maxi;
                --b,cre[pos].second=cre[pos].first*multi;
            } else b=0; // 没有收益
        }
        // debug1(pos);
        for(int i=0;i<n&&b;++i)
        {
            if(i==pos) continue;
            if(cre[i].first>cre[i].second)
            {
                --b;
                sum+=cre[i].first-cre[i].second;
            } else break;
        }
        printf("%lld\n",sum);
    }
    return 0;
}

/*

3 0 3
10 8
7 11
5 2
5 3 3
1 100
1 100
1 100
1 100
1 100
*/