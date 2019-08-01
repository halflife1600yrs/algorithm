#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
typedef long long ll;
ll val[MAXN],pows[62];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=pows[0]=1;i<62;++i) pows[i]=pows[i-1]<<1;
    for(int i=0;i<n;++i) scanf("%lld",&val[i]);
    for(int i=0,k=0;k<62;++k)
    { // i行k列
        // debug2(i,k);
        int j=i+1;
        if((val[i]&pows[k])==0)
        {
            for(;j<n;++j)
            { // 列主元
                if(val[j]&pows[k])
                {
                    swap(val[j],val[i]);
                    break;
                }
            }
        }
        if(j==n) continue;
        for(;j<n;++j)
        {
            if(val[j]&pows[k]) val[j]^=val[i];
        }
        ++i;
    }
    int rank=0;
    for(int i=0;i<n;++i)
        if(val[i]) ++rank;
    printf("%s\n",(rank&1ll)?"First":"Second");
    return 0;
}
/*
8
63 2 4 8 16 32 64 127
5
27 21 12 7 28
非空子集异或为0可以用高斯消元解决
矩阵的秩是关键，如果满秩就是有子集异或和为0
这题的博弈论的点就是判断秩为奇偶
 */