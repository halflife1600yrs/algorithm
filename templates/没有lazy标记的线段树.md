## 没有lazy标记的线段树

```c++
const int MAXN = 1e5 + 5;
typedef int Type;

Type val[MAXN];

namespace sgt
{ // 线段树区间/单点设置,单点/区间查询和/异或/与
int L[MAXN << 2], R[MAXN << 2], V[MAXN << 2];
const Type INIT = 0; // 值为init表示这个区间的值不一致,一定要保证init是不可能出现的值
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
{ // push_down的时候一定要注意值不能是INIT
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
    if(mid + 1 <= en) modifyLR(st, en, v, rson);
    if(V[lson] != V[rson]) // 更新当前信息
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
    if(V[pos] != INIT || l == r) // 区间值一样的话直接返回当前区间和查询区间相交的长度
        return (min(r, en) - max(st, l) + 1) * V[pos]; // init值非0的话这里要对l=r特判v是不是init
    if(en < l || r < st) return 0; // 这里返回的值应当是对结果没有影响的值.+-为0,^|为0,&为0xFFFFFFFF
    if(V[pos] != INIT) push_down(pos);
    Type ans = 0;
    if(st <= mid) ans += queryLR(st, en, lson);
    if(mid + 1 <= en) ans += queryLR(st, en, rson);
    return ans;
}

void push_to_bottom(int pos = 1)
{ // O(n)时间将信息全部推到底
    if(L[pos] == R[pos])
    {
        val[L[pos]] = V[pos]; // val保存底部信息,注意这里是val[L[pos]]
        return;
    }
    if(V[pos] != INIT) push_down(pos);
    push_to_bottom(lson), push_to_bottom(rson);
}
}
```

### 食用注意

1. `INIT`值一定要修改为不会出现的或是对结果没有影响的数
2. 所有的区间都是前闭后闭区间
3. `lson`、`rson`、`mid`都是宏
4. 区间查询非求和的时候要对`queryLR()`函数的操作仔细修改