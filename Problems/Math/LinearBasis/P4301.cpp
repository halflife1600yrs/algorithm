#include <bits/stdc++.h>

using namespace std;

const int MAXN=105,L=31;

struct linearbasis
{
    int b[L]; // 判断是否线性独立

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
} l_b;

int val[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&val[i]);
    sort(val,val+n,greater<int>());
    long long ans=0;
    for(int i=0;i<n;++i)
        if(l_b.insert(val[i]))
            ans+=val[i];
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-05 19:13:54 P4301
前置sg函数
线性基线性独立相关,求删去的数总和最小使一组数异或不为0
加入之前sort一下,使得小的数后加即可
==================================================================*/