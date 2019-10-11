## Splay

#### 基本操作：

```c++
namespace SplayTree
{
struct Node
{
    ll v;
    int cnt, size;
    int fa, son[2];
    Node(ll v = 0, int cnt = 1, int fa = -1) // 父节点为-1代表节点为root
        : v(v), cnt(cnt), size(1), fa(fa) { son[0] = son[1] = -1; }
    int& operator[](bool x) { return son[x]; }
} ns[MAXN];
int top, size, root; // size保存节点数
inline bool isrson(int id) { return id == ns[ns[id].fa].son[1]; }
void update(int id)
{
    if(~id) ns[id].size = ns[id].cnt
        + (ns[id][0] == -1 ? 0 : ns[ns[id][0]].size)
        + (ns[id][1] == -1 ? 0 : ns[ns[id][1]].size);
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
void splay(int id)
{ // id不能为-1
    for(int fa; ~(fa = ns[id].fa); rotate(id))
        if(~ns[fa].fa) rotate(isrson(id) == isrson(fa) ? fa : id);
    root = id;
}
int IDof(ll v)
{ // 查找v对应的节点位置,找不到就返回v作为新节点应插入的位置
    int id = root, last = root;
    for(; ~id; id = ns[last = id][ns[id].v < v])
        if(ns[id].v == v) return splay(id), id;
    return splay(last), -1;
}
int pre()
{ // 要求左子节点存在
    int id = ns[root][0];
    while(~ns[id][1]) id = ns[id][1];
    return id;
}
void insert(ll v, int k = 1)
{
    if(!size) // 空树
        ns[root = 0] = Node(v), top = size = 1;
    else if(~IDof(v))
        ns[root].cnt += k, ns[root].size += k;
    else
    { // 此时应该插入的位置已经转到根节点
        bool which = ns[root].v < v;
        ns[top] = Node(v, k, root);
        if(~ns[root][which]) ns[ns[root][which]].fa = top;
        swap(ns[top][which] = top, ns[root][which]);
        rotate(root = top++), ++size;
    }
}
void del(ll v, int k = 0x7FFFFFFF)
{
    if(IDof(v) == -1) return;
    if(ns[root].cnt > k)
        ns[root].cnt -= k, ns[root].size -= k;
    else if(ns[root][0] == -1 && ns[root][1] == -1)
        root = -1, size = top = 0;
    else if(ns[root][0] == -1)
        ns[root = ns[root][1]].fa = -1, --size;
    else if(ns[root][1] == -1)
        ns[root = ns[root][0]].fa = -1, --size;
    else
    {
        int leftbig = pre();
        ns[ns[leftbig][1] = ns[root][1]].fa = leftbig;
        ns[root = ns[root][0]].fa = -1, splay(leftbig);
        --size;
    }
}
}
```

#### k大、前驱后继、排名

```c++
int nxt()
{ // 要求右子节点存在
    int id = ns[root][1];
    while(~ns[id][0]) id = ns[id][0];
    return id;
}
int rankof(ll v)
{
    IDof(v);
    int lsize = ns[root][0] == -1 ? 1 : ns[ns[root][0]].size + 1;
    return ns[root].v < v ? lsize + ns[root].cnt : lsize;
}
ll kth_elm(int k)
{
    int id = root;
    while(k > 0)
        if(~ns[id][0] && k <= ns[ns[id][0]].size)
            id = ns[id][0];
        else
        { // 注意左节点不存在的情况
            int tmp = (~ns[id][0] ? ns[ns[id][0]].size : 0) + ns[id].cnt;
            if(k <= tmp) return ns[id].v;
            k -= tmp, id = ns[id][1];
        }
    return -1;
}
ll upper_bound(ll v, bool cmp = 1)
{ // cmp为1是小于
    IDof(v); // 注意判断相等的情况
    if(ns[root].v != v && (ns[root].v < v) == cmp) return ns[root].v;
    if(ns[root][!cmp] == -1) return -1;
    return ns[cmp ? pre() : nxt()].v;
}
```

