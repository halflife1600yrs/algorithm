#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5,INF=0x7f7f7f7f;

struct SgTree
{
    struct Node
    {
        int l,r,v;
        void set(int _l,int _r,int _v) { l=_l,r=_r,v=_v; }
    } nodes[MAXN<<2];
    void build(int start,int end,int pos=1)
    {
        nodes[pos].set(start,end,INF);
        if(end-start==1) return;
        int mid=(start+end)>>1;
        build(start,mid,pos<<1);
        build(mid,end,(pos<<1)+1);
    }
    void set(int x,int v,int pos=1)
    {
        nodes[pos].v=min(nodes[pos].v,v);
        if(nodes[pos].l==x&&nodes[pos].r==x+1) return;
        int mid=(nodes[pos].l+nodes[pos].r)>>1;
        if(x<mid) set(x,v,pos<<1);
        else set(x,v,(pos<<1)+1);
    }
    int query(int start,int end,int pos=1)
    {
        int l=nodes[pos].l,r=nodes[pos].r;
        if(start<=l&&r<=end) return nodes[pos].v;
        if(end<=l||r<=start) return INF;
        return min(query(start,end,pos<<1),query(start,end,(pos<<1)+1));
    }
} T;

int read()
{
    int ans=0;
    bool get=0;
    char c;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans*=10,ans+=c-'0',get=1;
        else if(get) break;
        else continue;
    }
    return ans;
}

int main()
{
    int n,q;
    n=read(),q=read();
    T.build(1,n+1);
    char c[5];
    for(int i=0;i<q;++i)
    {
        scanf("%s",c);
        int day,num;
        day=read(),num=read(); // 从1到n
        if(c[0]=='M') // 卖
        {
            T.set(num,day);
        } else if(c[0]=='D') // 查
        {
            int fr=num,to=n+1,mini,mid;
            mini=T.query(fr,to);
            if(mini>day) printf("-1\n");
            else
            {
                while(to-fr>1)
                {
                    mid=(fr+to)>>1;
                    mini=T.query(fr,mid);
                    if(mini<=day) to=mid;
                    else fr=mid;
                }
                printf("%d\n",fr);
            }
        }
    }
    return 0;
}