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

typedef unsigned long long ull;
typedef __int128_t i128;
typedef long double ld;

const int K1[5]={0,1,4,10,20};
const int K2[5]={0,2,8,20,40};

inline void print(i128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}

i128 fit(int x,const int* a)
{
    if(x<5) return a[x];
    i128 omega=1;
    i128 ans=0,tmp1,tmp2;
    for(int i=0;i<5;++i)
    {
        tmp1=a[i],tmp2=1;
        for(int j=0;j<5;++j)
            if(j!=i)
            {
                tmp1*=(x-j);
                tmp2*=(i-j);
            }
        // print(tmp1),puts(""),print(tmp2),puts("");
        if((tmp1/tmp2)*tmp2!=tmp1) puts("!!!");
        ans+=tmp1/tmp2;
    }
    return ans;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T,r,l;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d %d",&l,&r);
        --l,--r;
        // ull a=0,b=2*l+1,c=8*l+3,d=20*l+10,e=40*l+20;
        i128 a=fit(r-l,K1),b=fit(r-l,K2);
        // a=ceil(a),b=ceil(b);
        // debug2(a,b);
        printf("Case #%d: %llu\n",_,(ull)(b*l+a));
    }
    return 0;
}