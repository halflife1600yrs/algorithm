#include <bits/stdc++.h>

typedef long long ll;
const int sz = 1e5 + 5;
const int mode = 998244353;
typedef struct Tree
{
    int data, next;
} Tree;
Tree tree[2 * sz];
int node[sz], top;
bool vis[sz];

inline void add(int from, int to)
{
    tree[top].data = to, tree[top].next = node[from], node[from] = top, top++;
}

ll inv(int x)
{
    ll base = x, powr = mode - 2, ans = 1;
    while(powr)
    {
        if(powr & 1) ans = ans * base % mode;
        base = base * base % mode;
        powr >>= 1;
    }
    return ans;
}

ll dfs(int n, int depth)
{
    ll ans = depth;
    int next = node[n];
    vis[n] = 1;
    while(next != -1)
    {
        if(!vis[tree[next].data])
        {
            ll tmp = dfs(tree[next].data, depth + 1);
            ans = ans * tmp % mode * inv(ans + tmp) % mode;
        }
        next = tree[next].next;
    }
    return ans;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(vis, 0, sizeof(vis));
        std::fill(node, node + n + 1, -1);
        top = 0;
        int from, to;
        for(int i = 0; i < n - 1; i++)
        {
            scanf("%d %d", &from, &to);
            add(from, to), add(to, from);
        }
        ll ans = dfs(1, 1);
        printf("%lld\n", inv(ans));
    }
    return 0;
}

/*=======================================
added at 2018年10月10日 15:03:11	problem:NEWCODER156F
事件期望的和等于事件和的期望
一道做法十分奇特的期望题,与dp没有关系
想法十分,十分的巧妙:
对于任意一个结点,设它的深度为Di,那么当它被删掉时
注意是删掉而不是选中,因此这是对每个结点都存在的事件
它对期望的贡献就是(1/Di)*1(选中自己)+(Di-1)/Di*0(选中祖先)=1/Di
所以dfs所有结点,计算所有点的深度即可
!注意清空数组时n和n+1!
=======================================*/