#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=50005;

int val[MAXN];

namespace sgt
{
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    struct Node
    {
        int l,r,v;
    } ns[MAXN<<2];
    void build(int l,int r,int pos=1)
    {
        ns[pos].l=l,ns[pos].r=r;
        if(r-l==1)
        {
            ns[pos].v=val[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,lson),build(mid,r,rson);
        ns[pos].v=ns[lson].v+ns[rson].v;
    }
    void modify(int p,int a,int pos=1)
    {
        int r=ns[pos].r,l=ns[pos].l,mid=(l+r)>>1;
        ns[pos].v+=a;
        if(r-l==1) return;
        if(p<mid) modify(p,a,lson);
        if(p>=mid) modify(p,a,rson);
    }
    int sum(int fr,int to,int pos=1)
    {
        int r=ns[pos].r,l=ns[pos].l,mid=(l+r)>>1;
        if(fr<=l&&r<=to) return ns[pos].v;
        if(r<=fr||to<=l) return 0;
        return sum(fr,to,lson)+sum(fr,to,rson);
    }
}

int main()
{
    char s[10];
    int a,b;
    for(int T,_=scanf("%d",&T),n;T--;++_)
    {
        printf("Case %d:\n",_);
        scanf("%d",&n);
        for(int i=1;i<=n;++i) scanf("%d",&val[i]);
        sgt::build(1,n+1);
        while(scanf("%s",&s),strcmp(s,"End"))
        {
            scanf("%d %d",&a,&b);
            if(!strcmp(s,"Query"))
            {
                printf("%d\n",sgt::sum(a,b+1));
            } else if(!strcmp(s,"Add"))
            {
                sgt::modify(a,b);
            } else
            {
                sgt::modify(a,-b);
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-07-30 15:40:47	HDU1166
1
10
1 2 3 4 5 6 7 8 9 10
Query 1 3
Query 2 7
==================================================================*/