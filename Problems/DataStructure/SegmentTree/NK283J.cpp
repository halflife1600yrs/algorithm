#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int sz = 2e5 + 5;
int n;
struct SgTree
{
    int data[sz];
    int top;
    struct Node
    {
        int digit[32], mark;
        int fr, to, lson, rson;
        void init(int _fr, int _to, int _mark = 0) { fr = _fr, to = _to, mark = _mark; }
        void sets(int _l, int _r) { lson = _l, rson = _r; }
    } nodes[sz << 1];
    int build(int _fr = 0, int _to = n)
    {
        int cur = top++;
        nodes[cur].init(_fr, _to);
        if(_to - _fr == 1)
        {
            for(int i = 0, tmp = 1; i < 32; i++, tmp <<= 1)
                nodes[cur].digit[i] = data[_fr] & tmp ? 1 : 0;
            return cur;
        }
        int mid = (_fr + _to) / 2, lson = build(_fr, mid), rson = build(mid, _to);
        for(int i = 0; i < 32; i++)
        {
            nodes[cur].digit[i] = nodes[lson].digit[i] + nodes[rson].digit[i];
        }
        nodes[cur].sets(lson, rson);
        return cur;
    }
    void oper(int l, int r, int k, int pos = 0)
    {
        int _fr = nodes[pos].fr, _to = nodes[pos].to;
        if(l <= _fr && r >= _to)
        {
            nodes[pos].mark |= k;
            return;
        }
        int mid = (_fr + _to) / 2;
        int lson = nodes[pos].lson, rson = nodes[pos].rson;
        if(l < mid) oper(l, min(r, mid), k, lson);
        if(r > mid) oper(max(l, mid), r, k, rson);
        markdown(lson), markdown(rson); //这里将markdown放到if语句中会出错
        for(int i = 0; i < 32; i++)
            nodes[pos].digit[i] = nodes[lson].digit[i] + nodes[rson].digit[i];
    }
    ll markdown(int pos)
    {
        int lenz = nodes[pos].to - nodes[pos].fr, _mark = nodes[pos].mark;
        ll ans = 0;
        for(int i = 0, tmp = 1; i < 32; i++, tmp <<= 1)
        {
            if(_mark & tmp)
                ans += 1ll * lenz * tmp, nodes[pos].digit[i] = lenz;
            else
                ans += 1ll * nodes[pos].digit[i] * tmp;
        }
        int lson = nodes[pos].lson, rson = nodes[pos].rson;
        if(lson) nodes[lson].mark |= _mark;
        if(rson) nodes[rson].mark |= _mark;
        nodes[pos].mark = 0;
        return ans;
    }
    ll sum(int l, int r, int pos = 0)
    {
        int _fr = nodes[pos].fr, _to = nodes[pos].to;
        if(l <= _fr && r >= _to) return markdown(pos);
        if(nodes[pos].mark) markdown(pos);
        int mid = (_fr + _to) / 2, lson = nodes[pos].lson, rson = nodes[pos].rson;
        ll ans = 0;
        if(l < mid) ans += sum(l, min(r, mid), lson);
        if(r > mid) ans += sum(max(l, mid), r, rson);
        return ans;
    }
} stree;

int main()
{
    int m;
    while(~scanf("%d %d", &n, &m))
    {
        for(int i = 0; i < n; i++) scanf("%d", &stree.data[i]);
        stree.top = 0;
        stree.build();
        char order[5];
        int a, b, c;
        for(int i = 0; i < m; i++)
        {
            scanf("%s", order);
            if(!strcmp(order, "SUM"))
            {
                scanf("%d %d", &a, &b);
                printf("%lld\n", stree.sum(a - 1, b));
            }
            if(!strcmp(order, "OR"))
            {
                scanf("%d %d %d", &a, &b, &c);
                stree.oper(a - 1, b, c);
            }
        }
    }
    return 0;
}

/*=======================================
added at 2018年11月25日 17:41:36	problem:NK283J
线段树按位运算/求和
注意会爆int
=======================================*/