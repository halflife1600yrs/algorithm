#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
const int MAXN=1e6+5;
ll people[MAXN],tea[MAXN];

struct cmp
{
    bool operator()(const pll& a,const pii& b)
    {
        return a.first==b.first?a.second>b.second:a.first>b.first;
    }
};

priority_queue<pll,vector<pll>,cmp> q;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld %lld",&people[i],&tea[i]);
            q.push(pll(tea[i],i));
        }
        ll ans=0;
        int pos,num;
        pll tmp;
        for(int i=1;i<=n;++i)
        {
            while(people[i])
            {
                tmp=q.top(),q.pop();
                if(i!=tmp.second)
                {
                    if(tmp.first<people[i])
                    {
                        ans+=tmp.first;
                        people[i]-=tmp.first;
                    } else
                    {
                        q.push(pll(tmp.first,tmp.second-people[i]));
                        people[i]=0;
                    }
                } else
                {
                    if(q.top().first<people[i])
                    {
                        people[i]-=q.top().first,q.pop();
                    } else
                    {
                        q.push(pll(q.top().first,q.top().second-people[i]));
                        people[i]=0;
                    }
                    q.push(tmp);
                }
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-14 13:08:23 11
100
4
4 2
7 3
8 4
1 9

5
4 4
4 4
1 3
2 4
3 1
==================================================================*/