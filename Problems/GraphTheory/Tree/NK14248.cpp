#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1e5+5,MAXE=MAXV;
int V;
int a,b;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE<<1];

    int top, head[MAXV];

    void init() { top = 0, fill(head + 1, head + V + 1, -1); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    void dfs(int fr,int fa,int dis)
    {
        if(dis&1) ++a;
        else ++b;
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa) continue;
            dfs(to,fr,dis+1);
        }
    }
}

int main()
{
    scanf("%d",&V);
    G::init();
    int fr,to;
    for(int i=1;i<V;++i)
    {
        scanf("%d %d",&fr,&to);
        G::add(fr,to);
    }
    G::dfs(1,1,0);
    printf("%lld\n",(a*(a-1ll)+b*(b-1ll))>>1);
    return 0;
}

/*==================================================================
added at 2019-08-20 12:30:29 NK14248
思维题
两点直接路径的奇偶性和它们到根距离之和的奇偶性是一样的
因为lca以上的路径都算了两次
==================================================================*/