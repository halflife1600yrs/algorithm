#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV = 1e5 + 5, MAXE = MAXV * 2;
int val[MAXV];
ll _val[MAXV];

namespace sgt
{ // 区间加减求和
int L[MAXV << 2], R[MAXV << 2];
ll V[MAXV << 2], lazy[MAXV << 2];
#define lson (pos << 1)
#define rson (pos << 1 | 1)
#define mid ((l + r) >> 1)
void build(int l, int r, int pos = 1)
{
    L[pos] = l, R[pos] = r, lazy[pos] = 0;
    if(l == r)
        V[pos] = _val[l];
    else
        build(l, mid, lson), build(mid + 1, r, rson), V[pos] = V[lson] + V[rson];
}

void push_down(int pos)
{
    V[pos] += (R[pos] - L[pos] + 1) * lazy[pos];
    if(R[pos] > L[pos]) lazy[lson] += lazy[pos], lazy[rson] += lazy[pos]; // 不要直接赋值
    lazy[pos] = 0;
}

void addLR(int st, int en, ll v, int pos = 1)
{
    int l = L[pos], r = R[pos];
    if(st <= l && r <= en)
    {
        lazy[pos] += v; // 这里+=就不需要先push_down一次
        push_down(pos); // 这里一定要push_down,方便回退的时候更新上一层的值
        return;
    }
    if(lazy[pos]) push_down(pos); // 完全不命中也要push_down一次,方便上一层更新
    if(en < l || r < st) return;
    if(st <= mid)
        addLR(st, en, v, lson);
    else if(lazy[lson]) // 防止可能出现一半没有push_down的情况
        push_down(lson);
    if(mid + 1 <= en)
        addLR(st, en, v, rson);
    else if(lazy[rson])
        push_down(rson);
    V[pos] = V[lson] + V[rson]; // 更新当前信息
}

ll sumLR(int st, int en, int pos = 1)
{ // 记住查询的时候只有上层往下层push没有下层更新上层
    int l = L[pos], r = R[pos];
    if(en < l || r < st) return 0; // 完全不命中可以直接返回
    if(lazy[pos]) push_down(pos);
    if(st <= l && r <= en) return V[pos];
    ll ans = 0;
    if(st <= mid) ans += sumLR(st, en, lson);
    if(mid + 1 <= en) ans += sumLR(st, en, rson);
    return ans;
}
#undef lson
#undef rson
#undef mid
}

int v;

namespace T
{
struct Edge
{
    int to, last;
    void set(int _to, int _last) { to = _to, last = _last; }
} es[MAXE]; // 边记得开两倍!!!

int top, head[MAXV];

void init() { top = 0, memset(head, -1, sizeof(head)); }

void add(int fr, int to)
{
    es[top].set(to, head[fr]);
    head[fr] = top++;
}

int depth[MAXV], father[MAXV], son[MAXV], sz[MAXV]; //记录每个节点的深度,父亲,重儿子,子树大小

void dfs1(int fr, int fa)
{
    sz[fr] = 1;
    int maxi = 0;
    for(int i = head[fr], to; ~i; i = es[i].last)
    {
        to = es[i].to;
        if(to == fa) continue;
        father[to] = fr, depth[to] = depth[fr] + 1;
        dfs1(to, fr);
        sz[fr] += sz[to];
        if(sz[to] > maxi) son[fr] = to;
    }
}

int cnt, id[MAXV], chain[MAXV];

void dfs2(int fr, int ctop)
{
    id[fr] = ++cnt;
    _val[cnt] = val[fr]; // 注意一下线段树build的时候是用_val的值
    chain[fr] = ctop;
    if(sz[fr]==1) return;
    dfs2(son[fr], ctop);
    for(int i = head[fr], to; ~i; i = es[i].last)
    {
        to = es[i].to;
        if(to==father[fr]||to==son[fr]) continue;
        dfs2(to, to);
    }
}

void tree_cut()
{
    depth[1]=0;
    dfs1(1,1);
    cnt=0;
    dfs2(1,1);
    sgt::build(1,cnt);
}

void add_point(int a,ll v)
{
    sgt::addLR(id[a],id[a],v);
}

void add_path(int a,int b,ll v)
{
    while(chain[a]!=chain[b])
    {
        if(depth[chain[a]]<depth[chain[b]]) swap(a,b);
        sgt::addLR(id[chain[a]],id[a],v);
        a=father[chain[a]];
    }
    if(depth[a]>depth[b]) swap(a,b);
    sgt::addLR(id[a],id[b],v);
}

void add_subtree(int root,ll v)
{
    sgt::addLR(id[root],id[root]+sz[root]-1,v); // 这里注意要减1
}

ll query_path(int a,int b)
{
    ll ans=0;
    while(chain[a]!=chain[b])
    {
        if(depth[chain[a]]<depth[chain[b]]) swap(a,b);
        ans+=sgt::sumLR(id[chain[a]],id[a]);
        a=father[chain[a]];
    }
    if(depth[a]>depth[b]) swap(a,b);
    ans+=sgt::sumLR(id[a],id[b]);
    return ans;
}

ll query_subtree(int root)
{
    return sgt::sumLR(id[root],id[root]+sz[root]-1); // 这里注意要减1
}
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int q;
    scanf("%d %d",&v,&q);
    for(int i=1;i<=v;++i) scanf("%d",&val[i]);
    T::init();
    for(int i=1,fr,to;i<v;++i)
    {
        scanf("%d %d",&fr,&to);
        T::add(fr,to),T::add(to,fr);
    }
    T::tree_cut();
    int a,b,c;
    for(int i=0,op;i<q;++i)
    {
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d %d",&a,&b);
            T::add_point(a,b);
        } else if(op==2)
        {
            scanf("%d %d",&a,&b);
            T::add_subtree(a,b);
        } else if(op==3)
        {
            scanf("%d",&a);
            printf("%lld\n",T::query_path(1,a));
        }
    }
    return 0;
}