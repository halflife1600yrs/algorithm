#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
typedef int Type; // 要用ll的话直接这里改

namespace sgt
{ // 线段树区间/单点设置,单点/区间查询和/异或/与
struct Node
{ // 这里的修改是设置值所以不要lazy标记
    int l, r;
    Type v;
} ns[MAXN << 2];
const Type INIT = 0; // 值为init表示这个区间的值不一致,一定要保证init是不可能出现的值
#define lson (pos << 1)
#define rson (pos << 1 | 1)
#define mid ((l + r) >> 1) // 这里的括号不能省
void build(int l, int r, int v, int pos = 1)
{
    ns[pos].l = l, ns[pos].r = r, ns[pos].v = v;
    if(r == l) return;
    build(l, mid, v, lson), build(mid + 1, r, v, rson);
}

inline void push_down(int pos)
{
    ns[pos].v = ns[lson].v = ns[rson].v = ns[pos].v;
}

void modifyP(int p, Type v, int pos = 1)
{
    int l = ns[pos].l, r = ns[pos].r;
    if(l == r) ns[pos].v = v;
    if(l <= p && p <= mid)
        modifyP(p, v, lson);
    else if(mid + 1 <= p && p <= r)
        modifyP(p, v, rson);
    if(ns[lson].v != ns[rson].v)
        ns[pos].v = INIT;
    else
        ns[pos].v = ns[lson].v;
}

void modifyLR(int st, int en, Type v, int pos = 1)
{ // 区间设置值为v,注意这里st一定要保证比en小
    int l = ns[pos].l, r = ns[pos].r;
    if(st <= l && r <= en)
    { // 完全命中
        ns[pos].v = v;
        return;
    }
    if(en < l || r < st || ns[pos].v == v) return; // 完全不命中或者没有更新的必要
    if(ns[pos].v != INIT) push_down(pos); // 因为没有lazy标记所以这一步可以在上一种情况后面,否则不行
    if(st <= mid) modifyLR(st, en, v, lson);
    if(en >= mid + 1) modifyLR(st, en, v, rson);
    if(ns[lson].v != ns[rson].v)
        ns[pos].v = INIT;
    else
        ns[pos].v = ns[lson].v;
}

Type queryP(int p, int pos = 1)
{ // 单点查询
    int l = ns[pos].l, r = ns[pos].r;
    if(ns[pos].v != INIT || l == r) return ns[pos].v;
    if(ns[pos].v != INIT) push_down(pos);
    if(p <= mid)
        return queryP(p, lson);
    else
        return queryP(p, rson);
}

Type queryLR(int st, int en, int pos = 1)
{ // 这里的运算操作在不是求和的时候都要仔细修改
    int l = ns[pos].l, r = ns[pos].r;
    if(en < l || r < st) return 0; // 这里返回的值应当是对结果没有影响的值.+-为0,^|为0,&为0xFFFFFFFF
    if(ns[pos].v != INIT || l == r) // 区间值一样的话直接返回当前区间和查询区间相交的长度
        return (min(r, en) - max(st, l) + 1) * ns[pos].v; // init值非0的话这里要对l=r特判v是不是init
    if(ns[pos].v != INIT) push_down(pos);
    Type ans = 0;
    if(st <= mid) ans += queryLR(st, en, lson);
    if(en >= mid + 1) ans += queryLR(st, en, rson);
    return ans;
}
}

int main()
{

    return 0;
}