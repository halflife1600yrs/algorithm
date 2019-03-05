#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int n,m;
struct Graph
{
    int to[MAXN],in[MAXN];
    ll num[MAXN];
    bool vis[MAXN];
    void init()
    {
        memset(to,0,sizeof(to));
        memset(vis,0,sizeof(vis));
        memset(in,0,sizeof(in));
    }
    void add(int _fr,int _to)
    {
        to[_fr]=_to;
        ++in[_to];
    }
    void dlt()
    {
        queue<int> Q;
        for(int i=1;i<=n;++i)
            if(!in[i]) Q.push(i);
        int _fr,_to;
        while(!Q.empty())
        {
            _fr=Q.front();
            vis[_fr]=1,Q.pop();
            // debug1(_fr);
            _to=to[_fr];
            --in[_to],num[_to]+=num[_fr];
            if(!in[_to]) Q.push(_to);
        }
    }
    ll choose()
    {
        priority_queue<ll> Q;
        ll number;
        int start;
        for(int i=1;i<=n;++i)
            if(!vis[i])
            {
                start=i,vis[start]=1;
                number=num[start];
                for(int j=to[start];j!=start;j=to[j]) number+=num[j],vis[j]=1;
                Q.push(number);
            }
        ll ans=0;
        for(int i=0,end=Q.size();i<end&&i<m;++i) ans+=Q.top(),Q.pop();
        return ans;
    }
} G;

int main()
{
    scanf("%d %d",&n,&m);
    G.init();
    for(int i=1;i<=n;++i) scanf("%lld",&G.num[i]);
    for(int i=1,to;i<=n;++i)
    {
        scanf("%d",&to);
        G.add(i,to);
    }
    G.dlt();
    printf("%lld\n",G.choose());
    return 0;
}