```c++
typedef long long ll;
const int MAXV = 1e5 + 5, MAXE = MAXV * 2;
int val[MAXV];
ll _val[MAXV];

namespace sgt
{ // 区间加减求和线段树，注意build的时候用_val数组的值
}

struct T : Graph
{
int depth[MAXV], father[MAXV], son[MAXV], sz[MAXV]; //记录每个节点的深度,父亲,重儿子,子树大小

void dfs1(int fr, int fa)
{
    sz[fr] = 1;
    int maxi = 0;
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
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
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
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
};
```

