#include <bits/stdc++.h>

using namespace std;

typedef int ll;
const int MAXN = 1e5 + 5;
const ll INF = 0x7FFFFFFF;

struct Node
{
    ll v;
    bool tag;
    int size, fa, son[2];
    Node(ll v = 0, int fa = -1, int size = 1) // 父节点为-1代表节点为root
        : v(v), tag(0), size(size), fa(fa)
    {
        son[0] = son[1] = -1;
    }
    int& operator[](bool x) { return son[x]; }
};

namespace SplayTree
{
Node ns[MAXN];
int top, root;
void init(int n)
{ // 用于在翻转前加入INF和-INF
    root = 0;
    ns[0] = Node(-INF, -1, n + 2);
    ns[1] = Node(INF, 0, n + 1);
    ns[0][1] = 1;
    ns[1][0] = top = 2;
}
inline bool isrson(int id) { return id == ns[ns[id].fa].son[1]; }
void update(int id)
{
    if(~id) ns[id].size = 1 + (ns[id][0] == -1 ? 0 : ns[ns[id][0]].size)
        + (ns[id][1] == -1 ? 0 : ns[ns[id][1]].size);
}
void pushdown(int id)
{
    if(!ns[id].tag) return;
    swap(ns[id][0], ns[id][1]);
    if(~ns[id][0]) ns[ns[id][0]].tag ^= 1; // 注意这里不能覆盖
    if(~ns[id][1]) ns[ns[id][1]].tag ^= 1;
    ns[id].tag = 0;
}
void rotate(int id)
{ // id不能为根
    int fa = ns[id].fa, fafa = ns[fa].fa;
    bool which = (id == ns[fa][1]);
    ns[ns[fa][which] = ns[id][!which]].fa = fa;
    ns[ns[id][!which] = fa].fa = id;
    ns[id].fa = fafa;
    if(~fafa) ns[fafa][ns[fafa][1] == fa] = id;
    update(fa), update(id);
}
void splay(int id, const int aim = -1)
{ // id不能为-1
    for(int fa; (fa = ns[id].fa) != aim && ~fa; rotate(id))
        if(ns[fa].fa != aim) rotate(isrson(id) == isrson(fa) ? fa : id);
    if(aim == -1) root = id;
}
int build(int l, int r, int fa = 1)
{ // 前闭后开区间
    if(l == r) return -1;
    int mid = (l + r) >> 1, id = top++;
    ns[id] = Node(mid, fa, r - l);
    ns[id][0] = build(l, mid, id);
    ns[id][1] = build(mid + 1, r, id);
    return id;
}
int kth_elm(int k)
{
    int id = root;
    for(; pushdown(id), 1;)
        if(~ns[id][0] && k <= ns[ns[id][0]].size)
            id = ns[id][0];
        else
        { // 注意左节点不存在的情况
            k -= ~ns[id][0] ? ns[ns[id][0]].size + 1 : 1;
            if(!k) return id;
            id = ns[id][1];
        }
    return -1;
}
void reverse(int l, int r)
{ // 前闭后开,要求r>l+1
    int L = kth_elm(l - 1), R = kth_elm(r);
    splay(L), splay(R, L);
    ns[ns[R][0]].tag ^= 1; // 注意这里不能覆盖
    pushdown(ns[R][0]);
}
void dfs(int id = root)
{ // 中序遍历
    pushdown(id);
    if(~ns[id][0]) dfs(ns[id][0]);
    if(abs(ns[id].v) != INF) printf("%d ", ns[id].v);
    if(~ns[id][1]) dfs(ns[id][1]);
}
}

int main()
{
    int n, q, l, r;
    scanf("%d %d", &n, &q);
    SplayTree::init(n);
    SplayTree::build(1, n + 1); // 前闭后开
    while(q--)
    {
        scanf("%d %d", &l, &r);
        SplayTree::reverse(l + 1, r + 2); // INF和-INF的影响
    }
    SplayTree::dfs();
    return 0;
}

/*==================================================================
added at 2019-09-29 17:37:58 P3369
splay区间翻转模板
又忘记了打标记的时候不能覆盖
==================================================================*/