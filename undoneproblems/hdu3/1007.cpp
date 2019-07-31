#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 2e5 + 5, INF = 0x80808080;

int limit, ans[MAXN];
pii val[MAXN];

namespace sgt
{ // 区间加减求和
int L[MAXN << 2], R[MAXN << 2];
ll V[MAXN << 2], T[MAXN << 2], lazy[MAXN << 2], lazy2[MAXN << 2];
#define lson (pos << 1)
#define rson (pos << 1 | 1)
#define mid ((l + r) >> 1)
void build(int l, int r, int pos = 1)
{
    L[pos] = l, R[pos] = r, lazy[pos] = lazy2[pos] = 0, T[pos] = 1;
    if(l == r)
        V[pos] = val[l].first;
    else
        build(l, mid, lson), build(mid + 1, r, rson), V[pos] = max(V[lson], V[rson]);
}

void push_down(int pos)
{
    if(lazy[pos])
    {
        V[pos] += lazy[pos];
        if(R[pos] > L[pos]) lazy[lson] += lazy[pos], lazy[rson] += lazy[pos];
        lazy[pos] = 0;
    }
    if(lazy2[pos])
    {
        T[pos] += lazy2[pos];
        if(R[pos] > L[pos]) lazy2[lson] += lazy2[pos], lazy2[rson] += lazy2[pos];
        lazy2[pos] = 0;
    }
}

void addLR(int st, int en, ll v, int pos = 1)
{
    int l = L[pos], r = R[pos];
    if(st <= l && r <= en)
    {
        lazy[pos] += v, ++lazy2[pos]; // 这里+=就不需要先push_down一次
        push_down(pos); // 这里一定要push_down,方便回退到上一层的时候更新上一层的值
        return;
    }
    push_down(pos); // 完全不命中也要push_down一次,方便上一层更新
    if(en < l || r < st) return;
    if(st <= mid)
        addLR(st, en, v, lson);
    else
        push_down(lson);
    if(mid + 1 <= en)
        addLR(st, en, v, rson);
    else
        push_down(rson);
    V[pos] = max(V[lson], V[rson]);
    T[pos] = max(T[lson], T[rson]);
}

ll maxLR(int st, int en, int pos = 1)
{ // 记住查询的时候只有上层往下层push没有下层更新上层
    int l = L[pos], r = R[pos];
    if(en < l || r < st) return 0; // 完全不命中可以直接返回
    push_down(pos);
    if(st <= l && r <= en) return V[pos];
    ll ans;
    if(st <= mid) ans = maxLR(st, en, lson);
    if(mid + 1 <= en) ans = max(ans, max(ans, maxLR(st, en, rson)));
    return ans;
}

void push_to_bottom(int pos = 1)
{
    push_down(pos);
    if(L[pos] == R[pos])
    {
        // debug2(L[pos], V[pos]);
        // debug1(T[pos]);
        if(V[pos] == limit)
            ans[L[pos]] = T[pos];
        else
            ans[L[pos]] = T[pos] - 1;
        V[pos] = INF;
        return;
    }
    if(V[lson] + lazy[lson] >= limit) push_to_bottom(lson);
    if(V[rson] + lazy[rson] >= limit) push_to_bottom(rson);
    V[pos] = max(V[lson], V[rson]);
    T[pos] = max(T[lson], T[rson]);
}

#undef lson
#undef rson
#undef mid
}

bool cmp(const pii& a, const pii& b)
{
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

int main()
{
    int T, n;
    read(T);
    while(T--)
    {
        read(n),read(limit);
        for(int i = 1; i <= n; ++i)
            read(val[i].first), val[i].second = i;
        sgt::build(1, n);
        // sgt::push_to_bottom(); // 没必要,保证了放自己可行
        sort(val + 1, val + n + 1, cmp);
        int v, pos;
        for(int i = 1; i <= n; ++i)
        {
            v = val[i].first, pos = val[i].second;
            // debug2(v, pos);
            sgt::addLR(pos + 1, n, v);
            sgt::push_to_bottom();
        }
        for(int i = 1; i <= n; ++i)
            printf("%d ", ans[i] ? i - ans[i] : 0);
        printf("\n");
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 11:12:25 1007
2  
7 15  
1 2 3 4 5 6 7  
5 100  
80 40 40 40 60
==================================================================*/