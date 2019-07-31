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

const int SIZE = 32,MAXN=5e4+5;
typedef unsigned int ui;

template<typename Type, size_t SIZE>
struct l_b
{
    Type d[SIZE];
    l_b()
    {
        memset(d, 0, sizeof(d));
    }
    bool insert(Type val)
    {
        for(int i = SIZE - 1; i >= 0; --i)
            if(val & (1LL << i))
            {
                if(!d[i])
                {
                    d[i] = val;
                    break;
                }
                val ^= d[i];
            }
        return val > 0;
    }
    bool find(Type val) const
    {
        for(int i = SIZE - 1; i >= 0; --i)
            if(val & (1LL << i))
                val ^= d[i];
        return val > 0;
    }
};

typedef l_b<ui, 32> l_b32;

void merge(const l_b32& n1, const l_b32& n2,l_b32& n3)
{ // 这里n3可以等于n1不可以等于n2
    n3 = l_b32();
    for(int i = SIZE - 1; i >= 0; --i)
        if(n1.d[i]) // 能共同表示就加起来
            if(!n2.find(n1.d[i])) n3.insert(n1.d[i]);
}

namespace sgt
{
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    #define mid ((l+r)>>1)
    int L[MAXN<<2],R[MAXN<<2];
    l_b32 V[MAXN<<2];
    void build(int l,int r,int pos=1)
    {
        L[pos]=l,R[pos]=r;
        if(l==r)
        {
            int n;
            ui a;
            scanf("%d",&n);
            for(int i=0;i<n;++i)
            {
                scanf("%u",&a);
                V[pos].insert(a);
            }
        } else
        build(l,mid,lson),build(mid+1,r,rson),merge(V[lson],V[rson],V[pos]);
    }

    bool queryLR(int st,int en,ui x,int pos=1)
    { // 能表示-返回0
        if(!x) return 0;
        int l=L[pos],r=R[pos];
        // for(int i=0;i<32;++i) if(V[pos].d[i]) printf("%d-",V[pos].d[i]); printf("\n");
        if(st<=l&&r<=en) return V[pos].find(x);
        if(en<l||r<st) return 1;
        bool ans=0;
        if(st<=mid) ans|=queryLR(st,en,x,lson);
        if(mid+1<=en) ans|=queryLR(st,en,x,rson);
        debug2(l,r);
        debug1(x);
        return ans;
    }
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    sgt::build(1,n);
    int l,r;
    ui x;
    for(int i=0;i<q;++i)
    {
        scanf("%d %d %u",&l,&r,&x);
        // for(int i=0;i<32;++i) if(ans.d[i]) printf("%d-",ans.d[i]); printf("\n");
        if(!sgt::queryLR(l,r,x)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 20:51:41 NK884B
3 6

2 1 2
1 4
2 1 6

1 2 7
3 3 6
2 3 10
2 3 5
2 2 3
2 3 6

8 1
1 1
1 2
1 4
1 8
1 16
1 32
1 64
1 128
1 7 71
==================================================================*/