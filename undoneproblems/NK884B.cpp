#include <bits/stdc++.h>

using namespace std;

const int SIZE = 32,MAXN=5e4+5;

template<typename Type, size_t SIZE>
struct l_b
{
    Type d[SIZE], p[SIZE];
    int cnt;
    l_b()
    {
        memset(d, 0, sizeof(d));
        memset(p, 0, sizeof(p));
        cnt = 0;
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
    Type query_max()
    {
        Type ret = 0;
        for(int i = SIZE - 1; i >= 0; --i)
            if((ret ^ d[i]) > ret)
                ret ^= d[i];
        return ret;
    }
    Type query_min()
    {
        for(int i = 0; i < SIZE; i++)
            if(d[i])
                return d[i];
        return 0;
    }
    void rebuild()
    {
        for(int i = SIZE - 1; i >= 0; --i)
            for(int j = i - 1; j >= 0; j--)
                if(d[i] & (1LL << j))
                    d[i] ^= d[j];
        for(int i = 0; i < SIZE; i++)
            if(d[i])
                p[cnt++] = d[i];
    }
    Type kthquery(Type k)
    {
        int ret = 0;
        if(k >= (1LL << cnt))
            return -1;
        for(int i = 60; i >= 0; --i)
            if(k & (1LL << i))
                ret ^= p[i];
        return ret;
    }
};

typedef l_b<int, 32> l_b32;

l_b32 merge(const l_b32& n1, const l_b32& n2)
{
    l_b32 ret = n1;
    for(int i = SIZE - 1; i >= 0; --i)
        if(n2.d[i])
            ret.insert(n1.d[i]);
    return ret;
}

namespace sgt
{
    struct Node
    {
        Node *lson,*rson;
        l_b32 base;
    } ns[MAXN<<1];
    void build(int l,int r,int pos=0)
    {
        ns[pos].l=ns[pos].r
    }
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i = 0; i < n; ++i)
    {
    }
    return 0;
}