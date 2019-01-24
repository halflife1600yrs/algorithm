#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int n, camp[sz];
char comnd[8];
struct SgTree
{
    int top;
    struct Node
    {
        int infor;
        int l, r;
        int s, e;
    } node[(sz << 1) + 5];
    int build(int start = 1, int end = n + 1)
    {
        Node* cur = &node[top];
        cur->s = start, cur->e = end;
        if(end - start == 1)
            cur->infor = camp[start];
        else
        {
            int mid = (start + end) / 2;
            cur->l = ++top, cur->infor = build(start, mid);
            cur->r = ++top, cur->infor += build(mid, end);
        }
        return cur->infor;
    }
    int query(int start, int end, int node_n = 0)
    {
        Node* cur = &node[node_n];
        if(cur->e <= start || cur->s >= end) return 0;
        if(cur->s >= start && cur->e <= end) return cur->infor;
        return query(start, end, cur->l) + query(start, end, cur->r);
    }
    void add(int pos, int val, int node_n = 0)
    {
        Node* cur = &node[node_n];
        cur->infor += val;
        if(cur->s == pos && cur->e == pos + 1) return;
        if((cur->s + cur->e) / 2 > pos)
            add(pos, val, cur->l);
        else
            add(pos, val, cur->r);
    }
} EnemyInfor;

int main()
{
    int cas;
    scanf("%d", &cas);
    for(int time = 1; time <= cas; time++)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &camp[i]);
        EnemyInfor.top = 0, EnemyInfor.build();
        int a, b;
        printf("Case %d:\n", time);
        while(1)
        {
            scanf("%s", &comnd);
            if(!strcmp(comnd, "End")) break;
            if(!strcmp(comnd, "Add")) scanf("%d %d", &a, &b), EnemyInfor.add(a, b);
            if(!strcmp(comnd, "Sub")) scanf("%d %d", &a, &b), EnemyInfor.add(a, -b);
            if(!strcmp(comnd, "Query")) scanf("%d %d", &a, &b), printf("%d\n", EnemyInfor.query(a, b + 1));
        }
    }
    return 0;
}

/*=======================================
added at 2018年10月17日 19:16:40	problem:HDU1166
线段树单点修改
=======================================*/