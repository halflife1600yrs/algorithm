#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;

struct SgTree
{
    struct Node
    {
        int v;
        int l, r;
    } nodes[MAXN];

    void build(int l,int r,int v,int pos=0)
    {
        if(r-l==1)
        {
            nodes[pos].v=v;
            return;
        }
        nodes[pos].l=pos<<1,nodes[pos].r=pos<<1|1;
    }

    void change(int fr,int to,int v,int pos=0)
    {
        int l=nodes[pos].l,r=nodes[pos].r;
        if(fr<=l&&r<=to)
        {
            nodes[pos].v=v;
            return;
        }
        if(to<=l||r<=fr) return;
        change(fr,to,pos<<1),change(fr,to,pos<<1|1);
        if(nodes[pos<<1].v==nodes[pos<<1|1].v) nodes[pos].v=nodes[pos<<1].v;
        else nodes[pos].v=0;
    }

    int query(int at,int pos=0)
    {
        if(nodes[pos].v)
        {
            nodes[pos<<1].v=nodes[pos<<1|1].v=nodes[pos].v;
            return nodes[pos].v;
        }
        int l=nodes[pos].l,r=nodes[pos].r;
        int mid=(l+r)>>1;
        if(at>=mid) return query(at,pos<<1|1);
        return query(at,pos<<1);
    }
};
SgTree L,N;
int bucket[MAXN],val[MAXN];

int change(int del,int add,int tail)
{
    int cur
    int before=L.query(del),after=N.query(add);
    L.change(before+1,after+1,before);
    N.change(before,after,after);
    if(del)
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&val[i]);
        if(i<m) ++bucket[val[i]];
    }
    L.build(1,MAXN,0);
    N.build(1,MAXN,MAXN);
    int last=0,ans=0,sum=0,tail;
    for(int i=1,j=0;i<MAXN;++i)
    {
        if(bucket[i])
        {
            L.change(last+1,i+1,last); // last之前有其他的，所以L这里不改last
            N.change(last,i,i); // i之后可能有其他的，所以i这里不改
            last=i;
            if(j<k)
            {
                sum+=i;
                ++j;
            }
            if(j==k) tail=i;
        }
    }
    ans+=sum;
    for(int i=0,j=m;j<=n;++i,++j)
    {
        sum+=change(val[i],val[j],tail);
        ans+=sum;
    }
    return 0;
}