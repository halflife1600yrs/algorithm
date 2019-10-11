#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to)                                            \
    {                                                                 \
        std::cout << #arry " : ";                                     \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl;                                       \
    }

using namespace std;

typedef int ll;
const int MAXN = 1e5 + 5;

struct Node
{
    int fa, son[2];
    bool tag;
    ll v, sum;
    Node(ll v = 0, int fa = 0)
        : v(v), tag(0), sum(0), fa(fa) {}
    int& operator[](bool x) { return son[x]; }
} ns[MAXN];

namespace LCT
{
bool isrson(int id) { return id == ns[ns[id].fa][1]; }
bool noroot(int id)
{
    bool ans = (id == ns[ns[id].fa][1]) || (id == ns[ns[id].fa][0]);
    return ans;
}
// 判断是不是splay的root,注意splay的root不一定是path的最高点
void update(int id)
{ // 注意这里维护的是异或和,注意判断左右子树不存在
    ns[id].sum = ns[id].v ^ ns[ns[id][0]].sum ^ ns[ns[id][1]].sum;
}
void reverse(int id)
{ // 确保打上tag时子树已经交换
    swap(ns[id][0], ns[id][1]);
    ns[id].tag ^= 1;
}
inline void pushdown(int id)
{
    if(ns[id].tag)
    {
        ns[id].tag = 0;
        if(ns[id][0]) reverse(ns[id][0]);
        if(ns[id][1]) reverse(ns[id][1]);
    }
}
void pushall(int id)
{
    if(noroot(id)) pushall(ns[id].fa);
    pushdown(id);
}
void rotate(int id)
{ // id不能为根
    int fa = ns[id].fa, fafa = ns[fa].fa;
    if(noroot(fa)) ns[fafa][ns[fafa][1] == fa] = id; // 放在前面
    ns[id].fa = fafa;
    bool which = (id == ns[fa][1]);
    if(ns[fa][which] = ns[id][!which]) ns[ns[id][!which]].fa = fa;
    ns[ns[id][!which] = fa].fa = id;
    update(fa), update(id);
}
void splay(int id)
{ // id不能为0
    pushall(id);
    for(int fa; (fa = ns[id].fa), noroot(id); rotate(id))
        if(noroot(fa)) rotate(isrson(id) == isrson(fa) ? fa : id);
}
void expose(int id)
{
    for(int last = 0; id; id = ns[last = id].fa)
        splay(id), ns[id][1] = last, update(id);
}
void makeroot(int id) { expose(id), splay(id), reverse(id); }
int rootof(int id)
{ // id在原树中的根
    expose(id), splay(id);
    while(ns[id][0]) pushdown(id), id = ns[id][0]; // 一直往下找
    return splay(id), id;
}
ll split(int x, int y)
{
    makeroot(x), expose(y), splay(y);
    return ns[y].sum;
}
bool link(int x, int y)
{ // 先检查一下连边合法性
    makeroot(x);
    if(rootof(y) == x) return 0;
    return ns[x].fa = y, 1;
}
bool cut(int x, int y)
{
    makeroot(x); // 1.在同一棵树2.rootof之后y的父亲为x3.两点之间没有其他点
    if(rootof(y) != x || ns[y].fa != x || ns[y][0]) return 0;
    ns[y].fa = ns[x][1] = 0;
    return update(x), 1;
}
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", &ns[i].v), ns[i].sum = ns[i].v;
    while(q--)
    {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        switch(op)
        {
        case 0: printf("%d\n", LCT::split(x, y)); break;
        case 1: LCT::link(x, y); break;
        case 2: LCT::cut(x, y); break;
        case 3:
        {
            LCT::splay(x);
            ns[x].v = y;
            LCT::update(x);
        }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-10-06 22:52:02	P3690
动态树板子
常数异常大
==================================================================*/