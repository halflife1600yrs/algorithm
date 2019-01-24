#include <bits/stdc++.h>
using namespace std;
const int sz = 2e5 + 5;
int n, m, grade[sz];
struct SgTree
{
    struct Node
    {
        int infor;
        int l, r;
    } node[4 * sz];
    int build(int start = 1, int end = n + 1, int pos = 1)
    {
        node[pos].l = start, node[pos].r = end;
        int mid = (start + end) / 2;
        if(end - start == 1)
            node[pos].infor = grade[start];
        else
            node[pos].infor = max(build(start, mid, 2 * pos), build(mid, end, 2 * pos + 1));
        return node[pos].infor;
    }
    int query(int aim1, int aim2, int pos = 1)
    {
        if(node[pos].l >= aim2 || node[pos].r <= aim1) return 0;
        if(node[pos].l >= aim1 && node[pos].r <= aim2) return node[pos].infor;
        return max(query(aim1, aim2, 2 * pos), query(aim1, aim2, 2 * pos + 1));
    }
    void change(int aim, int x, int pos = 1)
    {
        if(node[pos].l == aim && node[pos].r == aim + 1)
        {
            node[pos].infor = x;
            return;
        }
        int mid = (node[pos].l + node[pos].r) / 2;
        if(mid > aim)
            change(aim, x, 2 * pos);
        else
            change(aim, x, 2 * pos + 1);
        node[pos].infor = max(node[2 * pos + 1].infor, node[2 * pos].infor);
    }
} Grade;
int main()
{
    while(~scanf("%d %d", &n, &m))
    {
        for(int i = 1; i <= n; i++) scanf("%d", &grade[i]);
        Grade.build();
        char op;
        int a, b;
        for(int i = 0; i < m; i++)
        {
            do
            {
                op = getchar();
            } while(op > 'Z' || op < 'A');
            if(op == 'Q') scanf("%d %d", &a, &b), printf("%d\n", Grade.query(a, b + 1));
            if(op == 'U') scanf("%d %d", &a, &b), Grade.change(a, b);
        }
    }
    return 0;
}

/*=======================================
added at 2018年10月18日 17:03:03	problem:HDU1754
线段树单点修改
=======================================*/