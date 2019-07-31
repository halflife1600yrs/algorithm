#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8005;
typedef int Type; // 要用ll的话直接这里改

Type val[MAXN];

namespace sgt
{ // 线段树区间/单点设置,单点/区间查询和/异或/与
int L[MAXN << 2], R[MAXN << 2], V[MAXN << 2];
const Type INIT = -1; // 值为init表示这个区间的值不一致,一定要保证init是不可能出现的值
#define lson (pos << 1)
#define rson (pos << 1 | 1)
#define mid ((l + r) >> 1) // 这里的括号不能省
void build(int l, int r, int v, int pos = 1)
{
    L[pos] = l, R[pos] = r, V[pos] = v;
    if(r == l) return;
    build(l, mid, v, lson), build(mid + 1, r, v, rson);
}

inline void push_down(int pos)
{
    V[lson] = V[rson] = V[pos];
}

void modifyP(int p, Type v, int pos = 1)
{
    int l = L[pos], r = R[pos];
    if(l == r) V[pos] = v;
    if(l <= p && p <= mid)
        modifyP(p, v, lson);
    else if(mid + 1 <= p && p <= r)
        modifyP(p, v, rson);
    if(V[lson] != V[rson])
        V[pos] = INIT;
    else
        V[pos] = V[lson];
}

void modifyLR(int st, int en, Type v, int pos = 1)
{ // 区间设置值为v,注意这里st一定要保证比en小
    int l = L[pos], r = R[pos];
    if(st <= l && r <= en)
    { // 完全命中
        V[pos] = v;
        return;
    }
    if(en < l || r < st || V[pos] == v) return; // 完全不命中或者没有更新的必要
    if(V[pos] != INIT) push_down(pos); // 因为没有lazy标记所以这一步可以在上一种情况后面,否则不行
    if(st <= mid) modifyLR(st, en, v, lson);
    if(en >= mid + 1) modifyLR(st, en, v, rson);
    if(V[lson] != V[rson])
        V[pos] = INIT;
    else
        V[pos] = V[lson];
}

Type queryP(int p, int pos = 1)
{ // 单点查询
    int l = L[pos], r = R[pos];
    if(V[pos] != INIT || l == r) return V[pos];
    if(V[pos] != INIT) push_down(pos);
    if(p <= mid)
        return queryP(p, lson);
    else
        return queryP(p, rson);
}

Type queryLR(int st, int en, int pos = 1)
{ // 这里的运算操作在不是求和的时候都要仔细修改
    int l = L[pos], r = R[pos];
    if(en < l || r < st) return 0; // 这里返回的值应当是对结果没有影响的值.+-为0,^|为0,&为0xFFFFFFFF
    if(V[pos] != INIT || l == r) // 区间值一样的话直接返回当前区间和查询区间相交的长度
        return (min(r, en) - max(st, l) + 1) * V[pos]; // init值非0的话这里要对l=r特判v是不是init
    if(V[pos] != INIT) push_down(pos);
    Type ans = 0;
    if(st <= mid) ans += queryLR(st, en, lson);
    if(en >= mid + 1) ans += queryLR(st, en, rson);
    return ans;
}

void push_to_bottom(int pos = 1)
{
    if(L[pos] == R[pos])
    {
        val[L[pos]] = V[pos];
        return;
    }
    if(V[pos] != INIT) push_down(pos);
    push_to_bottom(lson), push_to_bottom(rson);
}
}

int cnt[MAXN];

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(cnt, 0, sizeof(cnt));
        sgt::build(1, 8000, -1);
        for(int i = 0, l, r, c; i < n; ++i)
        {
            scanf("%d %d %d", &l, &r, &c);
            if(l < r) sgt::modifyLR(l + 1, r, c);
        }
        sgt::push_to_bottom();
        val[0] = -20;
        for(int i = 1; i <= 8000; ++i)
        {
            if(val[i] != val[i - 1] && val[i] >= 0) ++cnt[val[i]];
        }
        for(int i = 0; i <= 8000; ++i)
            if(cnt[i]) printf("%d %d\n", i, cnt[i]);
        printf("\n");
    }
    return 0;
}