#pragma GCC optimize ("O2")
#pragma G++ optimize ("O2")

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

typedef long long ll;
const int MODE=998244353;
inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

struct Mat
{
    int a[2][2];
    Mat() { a[0][0]=a[0][1]=a[1][0]=a[1][1]=0; }
    const int* operator[](int x) const { return a[x]; }
    int* operator[](int x) { return a[x]; }
    Mat operator*(const Mat& x) const // 带模矩阵乘法
    { // assert(col==x.lin);
        Mat ans;
        ans[0][0]=add(a[0][0]*(ll)x[0][0]%MODE,a[0][1]*(ll)x[1][0]%MODE);
        ans[0][1]=add(a[0][0]*(ll)x[0][1]%MODE,a[0][1]*(ll)x[1][1]%MODE);
        ans[1][0]=add(a[1][0]*(ll)x[0][0]%MODE,a[1][1]*(ll)x[1][0]%MODE);
        ans[1][1]=add(a[1][0]*(ll)x[0][1]%MODE,a[1][1]*(ll)x[1][1]%MODE);
        return ans;
    }
    Mat& operator*=(const Mat& x) { return *this = *this * x; }
};

Mat pows[62];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    ll Q,n;
    scanf("%lld %lld",&Q,&n);
    Q=min(500000ll,Q);
    pows[0][0][0]=3,pows[0][0][1]=2,pows[0][1][0]=1;
    for(int i=1;i<62;++i) pows[i]=pows[i-1]*pows[i-1];
    ll pref=0;
    int ans=0;
    for(int i=0;i<Q;++i)
    {
        Mat mul;
        mul[0][0]=mul[1][1]=1;
        ll m=n-1;
        // debug2(n,m);
        for(int j=0;j<62;++j)
            if((m>>j)&1)
                mul*=pows[j];
        ans=mul[0][0];
        // debug1(ans);
        n^=ans*(ll)ans;
        pref^=(ll)ans;
    }
    printf("%lld\n",pref);
    // cout<<clock()<<endl;
    return 0;
}