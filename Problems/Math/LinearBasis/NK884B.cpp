#include <bits/stdc++.h>

using namespace std;

const int MAXN=5e4+5;
typedef unsigned int ui;

template<int L>
struct linearbasis
{
    bitset<L> b[L];
    bool independent; // 判断是否线性独立

    linearbasis():independent(1) { memset(b,0,sizeof(b)); }

    bool insert(bitset<L> x)
    { // 插入失败返回1
        for(int i = L - 1; i >= 0; --i)
            if(x[i])
                if(b[i][i])
                    x ^= b[i];
                else
                { // 成功插入
                    b[i] = x;
                    return 0;
                }
        independent=0;
        return 1;
    }
    bool can_express(bitset<L> x)
    { // 能表示返回1
        for(int i = L - 1; i >= 0; --i)
            if(b[i][i]&&x[i])
                x ^= b[i];
        return x.none();
    }
};

void intersect(const linearbasis<32>& x,const linearbasis<32>& y,linearbasis<32>& z)
{
    z=linearbasis<32>();
    linearbasis<32> c=y,d=y;
    for(int i=0;i<32;++i)
    {
        bitset<32> a=x.b[i];
        if(a.none()) continue;
        int j=i;
        bitset<32> t=0;
        for(;j>=0;--j)
            if(a[j])
                if(c.b[j][j])
                    a^=c.b[j],t^=d.b[j];
                else break;
        if(a.none()) z.b[i]=t;
        else c.b[j]=a,d.b[j]=t;
    }
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    template<typename T>
    void read(T &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

namespace sgt
{
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    #define mid ((l+r)>>1)
    int L[MAXN<<2],R[MAXN<<2];
    linearbasis<32> V[MAXN<<2];
    void build(int l,int r,int pos=1)
    {
        L[pos]=l,R[pos]=r;
        if(l==r)
        {
            V[pos]=linearbasis<32>();
            int n;
            read(n);
            ui x;
            for(int i=0;i<n;++i)
                read(x),V[pos].insert(x);
            return;
        }
        build(l,mid,lson),build(mid+1,r,rson);
        intersect(V[lson],V[rson],V[pos]);
    }

    bool queryLR(int st,int en,int x,int pos=1)
    { // 可以表示返回1
        int l=L[pos],r=R[pos];
        if(st<=l&&r<=en) return V[pos].can_express(x);
        if(en<l||r<st) return 0;
        bool ans=1;
        if(st<=mid) ans&=queryLR(st,en,x,lson);
        if(mid+1<=en) ans&=queryLR(st,en,x,rson);
        return ans;
    }
}

int main()
{
    int n, q;
    read(n),read(q);
    sgt::build(1,n);
    int l,r;
    ui x;
    for(int i=0;i<q;++i)
    {
        read(l),read(r);
        read(x);
        if(!x) printf("YES\n");
        else if(sgt::queryLR(l,r,x)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 20:51:41 NK884B
线段树维护线性基的交
==================================================================*/