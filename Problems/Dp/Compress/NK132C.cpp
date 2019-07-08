#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e6+5;

bitset<MAXN> bits,last;

int main()
{
    int n,l,r;
    scanf("%d",&n);
    scanf("%d %d",&l,&r);
    for(int i=l;i<=r;++i) bits[i*i]=1;
    for(int i=1;i<n;++i)
    {
        scanf("%d %d",&l,&r);
        bits<<=(l*l);
        last=bits;
        for(int j=l+1;j<=r;++j)
        {
            last<<=((j<<1)-1);
            bits|=last;
        }
    }
    printf("%d\n",bits.count());
    return 0;
}

/*=======================================
added at 2019.May27 20:11:42	problem:NK132C
bitset优化dp
=======================================*/