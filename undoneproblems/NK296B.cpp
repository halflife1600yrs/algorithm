#include <bits/stdc++.h>

using namespace std;

const int sz = 1e6 + 5;
int n;
int arry[sz], pos[sz];
struct Node
{
    int fr, to;
    Node *lson, *rson;
    int data[4];
    void init(int _fr, int _to)
    {
        fr = _fr, to = _to;
        lson = rson = NULL;
        data[0] = 1, data[1] = n;
        data[2] = 1, data[3] = n;
    }
};
struct SgTree
{
    int top;
    Node nodes[sz << 1];
    void init()
    {
        top = 0;
        build();
        start = 1, end = n + 1, itv = 0;
        set(&nodes[0]);
        itv = 1, set(&nodes[0]);
    }
    Node* build(int fr = 1, int to = n + 1)
    {
        int cur = top++, mid = (fr + to) / 2;
        nodes[cur].init(fr, to);
        if(to - fr > 1)
        {
            nodes[cur].lson = build(fr, mid);
            nodes[cur].rson = build(mid, to);
        }
        return &nodes[cur];
    }
    int start, end;
    bool itv;
    void markdown(Node* pos)
    {
        int mark1 = pos->data[2 * itv], mark2 = pos->data[2 * itv + 1];
        Node *lson = pos->lson, *rson = pos->rson;
        if(lson != NULL)
        {
            if(lson->data[2 * itv] < mark1) lson->data[2 * itv] = mark1;
            if(rson->data[2 * itv] < mark1) rson->data[2 * itv] = mark1;
            if(lson->data[2 * itv + 1] > mark2) lson->data[2 * itv + 1] = mark2;
            if(rson->data[2 * itv + 1] > mark2) rson->data[2 * itv + 1] = mark2;
        }
    }
    void set(Node* pos)
    {
        int fr = pos->fr, to = pos->to;
        if(to <= start || end <= fr) return;
        markdown(pos);
        if(start <= fr && to <= end)
        {
            pos->data[2 * itv] = max(pos->data[2 * itv], start),
                          pos->data[2 * itv + 1] = min(end - 1, pos->data[2 * itv + 1]);
            return;
        }
        int mid = (fr + to) / 2;
        Node *lson = pos->lson, *rson = pos->rson;
        if(start < mid) set(lson);
        if(mid < end) set(rson);
    }
    Node* get(Node* pos)
    {
        markdown(pos);
        int fr = pos->fr, to = pos->to, mid = (fr + to) / 2;
        if(fr == start && to == start + 1) return pos;
        if(start < mid) return get(pos->lson);
        if(mid <= start)
            return get(pos->rson);
        else
            return NULL;
    }
} belt;

int main()
{
    int cas;
    for(scanf("%d", &cas); cas--;)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &arry[i]);
            pos[arry[i]] = i;
        }
        belt.init();
        int cur, next;
        Node *curnode, *nextnode;
        bool itv, able = 1;
        for(int i = 1; i < n; i++)
        {
            itv = belt.itv = i & 1;
            cur = pos[i], next = pos[i + 1];
            belt.start = cur, curnode = belt.get(&belt.nodes[0]);
            belt.start = next, nextnode = belt.get(&belt.nodes[0]);
            if(curnode->data[2 * itv] != nextnode->data[2 * itv]
                || curnode->data[2 * itv + 1] != nextnode->data[2 * itv + 1])
            {
                able = 0;
                break;
            }
            belt.start = min(cur, next), belt.end = max(cur, next) + 1;
            belt.set(&belt.nodes[0]);
        }
        if(able)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
/*=======================================
added at 2018年12月01日 17:27:16	problem:NK296
3
4
2 1 4 3
7
2 5 4 3 6 1 7
4
1 3 2 4
=======================================*/