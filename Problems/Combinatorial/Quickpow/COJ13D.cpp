#include <bits/stdc++.h>

using namespace std;

typedef __int128_t i128;
typedef long long ll;

ll mod;

struct mat
{
    i128 a,b,c,d;
    mat(i128 a=0,i128 b=0,i128 c=0,i128 d=0):a(a),b(b),c(c),d(d) {}
    void operator*=(const mat& x)
    {
        i128 A=(a*x.a+b*x.c)%mod,
             B=(a*x.b+b*x.d)%mod,
             C=(c*x.a+d*x.c)%mod,
             D=(c*x.b+d*x.d)%mod;
        a=A,b=B,c=C,d=D;
    }
};

int main()
{
    int T;
    ll n,a,b;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %lld %lld %lld",&n,&a,&b,&mod);
        mat A(2*b%mod,(a-b*(i128)b%mod+mod)%mod,1,0);
        mat B(1,0,0,1);
        for(--n;n;n>>=1,A*=A)
            if(n&1) B*=A;
        printf("%lld\n",(ll)((b*B.a+B.b)%mod));
    }
    return 0;
}

/*==================================================================
added at 2019-11-02 11:14:54 COJ13D
这题不能用带根号的快速幂因为最后需要除2
所以需要推出递推式然后用矩阵快速幂来做
==================================================================*/