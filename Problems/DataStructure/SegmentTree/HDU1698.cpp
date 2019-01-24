#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int n, m;
struct SgTree
{
    struct Node
    {
        int sum, l, r, mark;
    } node[(sz << 2) + 5];
    void build(int start = 1, int end = n + 1, int pos = 1)
    {
        node[pos].l = start, node[pos].r = end, node[pos].sum = end - start, node[pos].mark = 0;
        if(end - start == 1) return;
        int mid = (start + end) / 2;
        build(start, mid, 2 * pos), build(mid, end, 2 * pos + 1);
    }
    void markdown(int pos)
    {
        int x = node[pos].mark;
        node[pos].sum = (node[pos].r - node[pos].l) * x;
        node[2 * pos].mark = x, node[2 * pos + 1].mark = x, node[pos].mark = 0;
    }
    void set(int start, int end, int val, int pos = 1)
    {
        if(node[pos].mark) markdown(pos);
        if(node[pos].l >= end || node[pos].r <= start) return;
        if(node[pos].r - node[pos].l == 1)
        {
            node[pos].sum = val;
            return;
        }
        if(node[pos].l >= start && node[pos].r <= end)
        {
            node[pos].mark = val, markdown(pos);
            return;
        }
        set(start, end, val, 2 * pos), set(start, end, val, 2 * pos + 1);
        node[pos].sum = node[2 * pos].sum + node[2 * pos + 1].sum;
    }
} Hook;
int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int cas;
    scanf("%d", &cas);
    for(int time = 1; time <= cas; time++)
    {
        scanf("%d %d", &n, &m);
        Hook.build();
        int a, b, c;
        for(int i = 0; i < m; i++) scanf("%d %d %d", &a, &b, &c), Hook.set(a, b + 1, c);
        if(Hook.node[1].mark) Hook.markdown(0);
        printf("Case %d: The total value of the hook is %d.\n", time, Hook.node[1].sum);
    }
    return 0;
}

/*=======================================
added at 2018年10月19日 20:26:03	problem:HDU1698
线段树区间修改
=======================================*/