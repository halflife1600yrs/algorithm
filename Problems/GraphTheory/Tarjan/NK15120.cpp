#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXV=505,MAXE=MAXV*MAXV;
int V,E,in[MAXV];
bool able[MAXV],_able[MAXV],sz[MAXV];
 
namespace S
{
int data[MAXV], t;
inline void push(int x) { data[t++] = x; }
inline int top() { return data[t - 1]; }
}
 
namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];
 
    int top, head[MAXV];
 
    void init() { top = 0, fill(head, head + V + 4, -1); }
 
    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
 
    int dfn[MAXV], low[MAXV], dfs_num;
    bool ins[MAXV];
 
    void dfs(int fr)
    {
        dfn[fr] = low[fr] = ++dfs_num;
        ins[fr] = 1, S::push(fr);
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(!dfn[to])
            {
                dfs(to);
                low[fr] = min(low[fr], low[to]);
            } else if(ins[to])
                low[fr] = min(low[fr], dfn[to]);
        }
        if(dfn[fr] == low[fr])
        {
            sz[low[fr]]=1;
            while(S::top() != fr)
            {
                low[S::top()] = dfn[fr];
                ins[S::top()] = 0;
                --S::t;
            }
            ins[fr] = 0;
            --S::t;
        }
    }
 
    void tarjan()
    {
        // fill(dfn + 1, dfn + 1 + V, 0);
        // fill(ins + 1, ins + 1 + V, 0);
        dfs_num = S::t = 0;
        for(int i = 1; i <= V; ++i)
            if(!dfn[i]) dfs(i);
    }
 
    void check()
    {
        for(int fr=1;fr<=V;++fr)
            for(int i=head[fr];~i;i=edges[i].last)
                if(low[fr]!=low[edges[i].to])
                    ++in[low[edges[i].to]];
    }
}
 
int main()
{
    int m;
    scanf("%d %d",&V,&m);
    for(int i=0,x;i<m;++i)
        scanf("%d",&x),able[x]=1;
    G::init();
    for(int i=1,n,to;i<=V;++i)
    {
        scanf("%d",&n);
        for(int j=0;j<n;++j)
        {
            scanf("%d",&to);
            G::add(i,to);
        }
    }
    G::tarjan();
    G::check();
    int ans=0;
    for(int i=1;i<=V;++i)
        if(able[i]) _able[G::low[i]]=1;
    for(int i=1;i<=V;++i)
    {
        if(sz[i]&&!in[i])
        {
            if(_able[i]) ++ans;
            else
            {
                ans=-1;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
 
/*==================================================================
added at 2019-08-20 10:19:12 NK15120
6 2
1 2
1 2
2 4 5
2 1 6
3 3 5 6
0
0
绝对不要用原来的点判断强连通分量因为会出现重复
tarjan判断强连通分量的时候要同时判断其sz是否大于0
==================================================================*/