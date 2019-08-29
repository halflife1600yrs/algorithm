#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1e5 + 5, MAXE = 6e5 + 5, DEP = 18;
const int INF = 0x7f7f7f7f;
typedef long long ll;
typedef pair<int, int> pii;
int V, E;
pair<int, pii> Es[MAXE];
bool used[MAXE];
inline pii combine(const pii& a, const pii& b)
{ // 合并区间严格最大值次大值信息
    pii ans(max(a.first, b.first), max(a.second, b.second));
    if(min(a.first, b.first) != ans.first)
        ans.second = max(ans.second, min(a.first, b.first));
    return ans;
}
namespace T
{
struct Edge
{
    int to, last, l;
    void set(int _to, int _last, int _l = 0) { to = _to, last = _last, l = _l; }
} edges[2 * MAXV];
int top, head[MAXV];
void init() { top = 0, fill(head + 1, head + V + 1, -1); }
void add(int fr, int to, int l = 0)
{
    edges[top].set(to, head[fr], l);
    head[fr] = top++;
}
int fa[MAXV][DEP], depth[MAXV];
pii lenz[MAXV][DEP];
void build_lca(int fr)
{
    for(int i = 1; (1 << i) <= depth[fr]; ++i)
    {
        fa[fr][i] = fa[fa[fr][i - 1]][i - 1];
        lenz[fr][i]=combine(lenz[ fa[fr][i-1] ][i-1],lenz[fr][i-1]);
    }
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(to == fa[fr][0]) continue;
        fa[to][0] = fr, depth[to] = depth[fr] + 1;
        lenz[to][0] = pii(edges[i].l, 0);
        build_lca(to);
    }
}
pii lca(int a, int b)
{
    pii ans;
    if(depth[a] < depth[b]) swap(a, b);
    for(int i = DEP - 1; i >= 0; --i)
        if(depth[a] - (1 << i) >= depth[b])
        {
            ans = combine(ans, lenz[a][i]);
            a = fa[a][i];
        }
    if(a == b) return ans;
    for(int i = DEP - 1; i >= 0; --i)
        if(fa[a][i] != fa[b][i])
        {
            ans = combine(ans, combine(lenz[b][i], lenz[a][i]));
            a = fa[a][i], b = fa[b][i];
        }
    ans = combine(ans, combine(lenz[a][0], lenz[b][0]));
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
ll Kruskal()
{
    sort(Es, Es + E);
    for(int i = 1; i <= V; ++i) uset[i] = i;
    int fr, to, x, y, l, cnt = 0;
    ll ans = 0;
    for(int i = 0; i < E; ++i)
    {
        tie(fr, to) = Es[i].second;
        x = get_fa(fr), y = get_fa(to);
        if(x == y) continue;
        ans += (l = Es[i].first);
        used[i] = 1, ++cnt;
        uset[y] = x;
        T::add(fr, to, l), T::add(to, fr, l);
    }
    if(cnt != V - 1) return -1;
    return ans;
}
}
int main()
{
    scanf("%d %d", &V, &E);
    for(int i = 0, fr, to, l; i < E; ++i)
    {
        scanf("%d %d %d", &fr, &to, &l);
        Es[i] = pair<int, pii>(l, pii(fr, to));
    }
    T::init();
    ll mst = K::Kruskal();
    T::build_lca(1);
    int md, smd, diff = INF;
    for(int i = 0, fr, to; i < E; ++i)
        if(!used[i])
        {
            tie(fr, to) = Es[i].second;
            tie(md, smd) = T::lca(fr, to);
            if(Es[i].first > md) diff = min(diff, Es[i].first - md);
            else if(smd && Es[i].first > smd)
                diff = min(diff, Es[i].first - smd);
        }
    printf("%lld\n", mst + diff);
    return 0;
}
/*==================================================================
added at 2019-08-27 15:54:48 P4180
inline pii combine(const pii& a,const pii& b)
{ // 合并区间非严格最大值次大值信息
    pii ans(a);
    if(b.first>a.first)
        ans.second=max(a.first,b.second),ans.first=b.first;
    else ans.second=max(a.second,b.first);
    return ans;
}
inline pii combine(const pii& a,const pii& b)
{ // 合并区间严格最大值次大值信息
    pii ans;
    ans.first=max(a.first,b.first);
    ans.second=max(a.second,b.second);
    if(min(a.first,b.first)!=ans.first)
        ans.second=max(ans.second,min(a.first,b.first));
    return ans;
}
==================================================================*/