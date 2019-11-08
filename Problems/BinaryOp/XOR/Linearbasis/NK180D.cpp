#include <bits/stdc++.h>

using namespace std;

const int L=30;

struct linearbasis
{
    int b[L];

    bool insert(int x)
    { // 插入失败返回1
        for(int i = L - 1; i >= 0; --i)
            if(x&(1<<i))
                if(b[i])
                    x ^= b[i];
                else
                { // 成功插入
                    b[i] = x;
                    return 0;
                }
        return 1;
    }
    bool can_express(int x)
    { // 能表示返回1
        for(int i = L - 1; i >= 0; --i)
            if(b[i] && (x&(1<<i)))
                x ^= b[i];
        return x==0;
    }
} l_b;

int main()
{
    int n,q,x,y;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&x),l_b.insert(x);
    scanf("%d",&q);
    for(int i=0;i<q;++i)
    {
        scanf("%d %d",&x,&y);
        if(l_b.can_express(x^y)) puts("YES");
        else puts("NO");
    }
    return 0;
}