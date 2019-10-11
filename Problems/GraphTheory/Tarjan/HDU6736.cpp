#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=3e5+5,MAXE=1e6+5,MODE=998244353;
int V,E,ans;

int quick_pow(int base,int ind)
{
    int ans=1;
    for(;ind;base=base*(ll)base%MODE,ind>>=1)
        if(ind&1) ans=ans*(ll)base%MODE;
    return ans;
}

namespace S
{
    int data[MAXV],t;
    inline void push(int x) { data[t++]=x; }
    inline int top() { return data[t-1]; }
}

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
    int depth[MAXV];
    bool ins[MAXV];
    void dfs(int fr,int fa,int d)
    {
        depth[fr]=d;
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa) continue;
            if(!depth[to]) dfs(to,fr,d+1);
            else if(depth[fr]>depth[to])
            {
                ans=ans*(quick_pow(2,depth[fr]-depth[to]+1)+MODE-1ll)%MODE;
                E-=depth[fr]-depth[to]+1;
            }
        }
    }
    void tarjan()
    {
        fill(depth,depth+V+1,0);
        for(int i=1;i<=V;++i)
            if(!depth[i]) dfs(i,-1,1);
    }
}

int main()
{
    while(~scanf("%d %d",&V,&E))
    {
        G::init();
        for(int i=0,fr,to;i<E;++i)
        {
            scanf("%d %d",&fr,&to);
            G::add(fr,to),G::add(to,fr);
        }
        ans=1;
        G::tarjan();
        printf("%d\n",ans*(ll)quick_pow(2,E)%MODE);
    }
    return 0;
}

/*==================================================================
added at 2019-09-28 14:15:57 2019CCPC秦皇岛F
可能是第一道仙人掌的题目?
点双的内容都有点忘了,不过其实dfs就行
==================================================================*/