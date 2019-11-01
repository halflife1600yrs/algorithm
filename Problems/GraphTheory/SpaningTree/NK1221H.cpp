#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>
#include <map>
 
using namespace std;
 
const int MAXV = 2e5 + 5, MAXE = 5e5 + 5, DEP = 20;
const int INF = 0x7f7f7f7f;
typedef long long ll;
typedef pair<int, int> pii;
int V, E;
pair<int, pii> Es[MAXE];
bool used[MAXE];
 
namespace T
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE];
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to, int l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    int fa[MAXV][DEP], depth[MAXV];
    int lenz[MAXV][DEP];
    void build_lca(int fr)
    {
        for(int i = 1; (1 << i) <= depth[fr]; ++i)
        {
            fa[fr][i] = fa[fa[fr][i - 1]][i - 1];
            lenz[fr][i]=max(lenz[ fa[fr][i-1] ][i-1],lenz[fr][i-1]);
        }
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(to == fa[fr][0]) continue;
            fa[to][0] = fr, depth[to] = depth[fr] + 1;
            lenz[to][0] = edges[i].l;
            build_lca(to);
        }
    }
    int lca(int a, int b)
    {
        int ans = -INF;
        if(depth[a] < depth[b]) swap(a, b);
        for(int i = DEP - 1; i >= 0; --i)
            if(depth[a] - (1 << i) >= depth[b])
            {
                ans = max(ans, lenz[a][i]);
                a = fa[a][i];
            }
        if(a == b) return ans;
        for(int i = DEP - 1; i >= 0; --i)
            if(fa[a][i] != fa[b][i])
            {
                ans = max(ans,max(lenz[b][i], lenz[a][i]));
                a = fa[a][i], b = fa[b][i];
            }
        ans = max(ans,max(lenz[a][0], lenz[b][0]));
        return ans;
    }
}
 
namespace K
{
    int uset[MAXV];
    int get_fa(int x)
    {
        if(uset[x] == x) return x;
        return uset[x] = get_fa(uset[x]);
    }
    void Kruskal()
    {
        sort(Es, Es + E);
        for(int i = 1; i <= V; ++i) uset[i] = i;
        int fr, to, x, y, l;
        for(int i = 0; i < E; ++i)
        {
            tie(fr, to) = Es[i].second;
            x = get_fa(fr), y = get_fa(to);
            if(x == y) continue;
            l = Es[i].first;
            used[i] = 1, uset[y] = x;
            T::add(fr, to, l), T::add(to, fr, l);
        }
    }
}
 
int main()
{
    scanf("%d %d",&V,&E);
    T::init();
    for(int i=0,fr,to,l;i<E;++i)
    {
        scanf("%d %d %d", &fr, &to, &l);
        Es[i] = pair<int, pii>(l, pii(fr, to));
    }
    K::Kruskal();
    T::build_lca(1);
    ll ans=0;
    for(int i=0,fr,to;i<E;++i)
        if(!used[i])
        {
            tie(fr,to)=Es[i].second;
            if(T::lca(fr,to)>=Es[i].first)
                ans+=Es[i].first;
        }
    printf("%lld\n",ans);
    return 0;
}

/*
LCA合并左右两边信息之后还要和ans合并
*/