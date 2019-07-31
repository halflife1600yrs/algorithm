#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;

ll val[MAXN];

namespace sgt
{ // 区间加减求和
int L[MAXN << 2], R[MAXN << 2];
ll V[MAXN << 2], lazy[MAXN << 2];
#define lson (pos << 1)
#define rson (pos << 1 | 1)
#define mid ((l + r) >> 1)
void build(int l, int r, int pos = 1)
{
    L[pos] = l, R[pos] = r, lazy[pos] = 0;
    if(l == r)
        V[pos] = val[l];
    else
        build(l, mid, lson), build(mid + 1, r, rson), V[pos] = V[lson] + V[rson];
}

void push_down(int pos)
{
    V[pos] += (R[pos] - L[pos] + 1) * lazy[pos];
    if(R[pos]>L[pos]) lazy[lson] += lazy[pos], lazy[rson] += lazy[pos];
    lazy[pos] = 0;
}

void addLR(int st, int en, ll v, int pos = 1)
{
    int l = L[pos], r = R[pos];
    if(st <= l && r <= en)
    {
        lazy[pos] += v; // 这里+=就不需要先push_down一次
        push_down(pos); // 这里一定要push_down,方便回退到上一层的时候更新上一层的值
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
    V[pos] = V[lson] + V[rson];
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

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%lld", &val[i]);
    sgt::build(1, n);
    int pattern, l, r;
    ll v;
    for(int i = 0; i < q; ++i)
    {
        // printf("\n\n");
        scanf("%d", &pattern);
        if(pattern == 1)
        {
            scanf("%d %d %lld", &l, &r, &v);
            sgt::addLR(l, r, v);
        } else
        {
            scanf("%d %d", &l, &r);
            printf("%lld\n", sgt::sumLR(l, r));
        }
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 11:12:25 1007
8 10
1 5 8 39
2 5 8
1 3 6 3
1 5 8 90
1 1 5 21
2 3 8
1 3 8 17
1 4 7 52
2 2 6
1 2 7 41

2313
4281
3278
==================================================================*/