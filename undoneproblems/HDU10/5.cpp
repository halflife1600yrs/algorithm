#include<bits/stdc++.h>
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
typedef pair<ll,ll> pii;

const ll Inf = 2e18;
const int MAXN=1e5+5;

int n;
ll maxx;
ll x[MAXN],y[MAXN];
pii nx[MAXN],ny[MAXN];

bool cmp1(const pii& a,const pii& b)
{
    return a.first==b.first?a.second<b.second:a.first>b.first;
}

int main()
{
    int T;
    scanf("%d",&T);
    while( T-- )
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%lld %lld",&x[i],&y[i]);
            nx[i].first=x[i],ny[i].first=y[i];
            nx[i].second=ny[i].second=i;
        }
        sort(nx,nx+n,cmp1);
        sort(ny,ny+n,cmp1);
        ll maxy = -1,ans = Inf,tmp;
        pii *pos;
        for(int i=0;i<=n-1;i++)
        {
            // debug2(maxy,nx[i].first);
            if( maxy >= nx[i].first )
            {
                ans = min(ans,maxy-nx[i].first);
            } else
            {
                // debug2(nx[i].first,nx[i].second);
                pos=lower_bound(ny,ny+n,nx[i],cmp1);
                // debug2(pos->first,pos->second);
                // debug1(pos-ny);
                if(pos->second!=nx[i].second) ans=min(nx[i].first-pos->first,ans);
                else if(pos-ny<=n-1) ans=min(nx[i].first-(pos+1)->first,ans);//,puts("!!!");
                // debug2((pos-1)->first,(pos-1)->second);
                if((--pos)>=ny)
                {
                    if(pos->second==nx[i].first)
                    {
                        if((--pos)>=ny) ans=min(ans,pos->first-nx[i].first);
                    } else
                    {
                        ans=min(pos->first-nx[i].first,ans);
                    }
                }
            }
            if( y[nx[i].second] > maxy )  maxy = y[nx[i].second];
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
10
1 3
3 6
4 4
4 1
5 3
6 3
7 2
8 2
5 5
4 5
4
5 5
5 5
5 5
5 5
1
2
1 1
7 7
10
7 7
1 1
1
7
1 5
2 5
3 5
4 5
6 5
7 5
8 5
*/