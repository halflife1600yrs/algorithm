#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN=100005;
int n,m;
int val[MAXN];

struct SgTree
{
    struct Node
    {
        int l,r;
        ll val,mark;
    } nodes[MAXN<<2];
    void build(int fr,int to,int pos=1)
    {
        nodes[pos].l=fr,nodes[pos].r=to;
        if(to-fr==1)
        {
            nodes[pos].val=val[fr];
            return;
        }
        int mid=(fr+to)>>1;
        build(fr,mid,pos<<1);
        build(mid,to,(pos<<1)+1);
        nodes[pos].val=nodes[pos<<1].val+nodes[(pos<<1)+1].val;
    }
    void markdown(int pos)
    {
        int mark=nodes[pos].mark,l=nodes[pos].r-nodes[pos].l;
        if(!nodes[pos].mark) return;
        if(l>1)
        {
            nodes[pos<<1].mark+=mark;
            nodes[(pos<<1)+1].mark+=mark;
        }
        nodes[pos].val+=l*mark;
        nodes[pos].mark=0;
    }
    ll add(int fr,int to,int v,int pos=1)
    {
        // debug2(fr,to);
        int l=nodes[pos].l,r=nodes[pos].r;
        // debug2(l,r);
        // debug1(pos);
        if(fr<=l&&r<=to)
        {
            nodes[pos].mark+=v;
            markdown(pos);
            return nodes[pos].val;
        }
        markdown(pos);
        if(to<=l||r<=fr) return nodes[pos].val;
        nodes[pos].val=add(fr,to,v,pos<<1)+add(fr,to,v,(pos<<1)+1);
        return nodes[pos].val;
    }
    ll sum(int fr,int to,int pos=1)
    {
        int l=nodes[pos].l,r=nodes[pos].r;
        markdown(pos);
        if(fr<=l&&r<=to) return nodes[pos].val;
        if(to<=l||r<=fr) return 0;
        return sum(fr,to,pos<<1)+sum(fr,to,(pos<<1)+1);
    }
} sgt;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i) scanf("%d",&val[i]);
    sgt.build(0,n);
    for(int i=0,op,x,y;i<m;++i)
    {
        ll v;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d %d %lld",&x,&y,&v);
            sgt.add(x-1,y,v);
        } else if(op==2)
        {
            scanf("%d %d",&x,&y);
            printf("%lld\n",sgt.sum(x-1,y));
        }
    }
    return 0;
}

/*=======================================
added at 2019.Mar30 16:42:29	problem:P3372
线段树模板题
=======================================*/