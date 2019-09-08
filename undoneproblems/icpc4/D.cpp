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

typedef pair<int,int> pii;
typedef long long ll;
const int MAXN=1e5+5,MODE=100003;

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

int quick_pow(int x,int ind)
{
    int ans=1;
    for(;ind;x=x*(ll)x%MODE,ind>>=1)
        if(ind&1) ans=ans*(ll)x%MODE;
    return ans;
}

struct Mat
{
    int a[3][3];
    Mat()
    {
        a[0][0]=a[0][1]=a[0][2]=
        a[1][0]=a[1][1]=a[1][2]=
        a[2][0]=a[2][1]=a[2][2]=0;
    }
    Mat(const Mat& x) // 拷贝构造函数
    {
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
                a[i][j]=x[i][j];
    }
    Mat& operator=(const Mat& x)
    {
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
                a[i][j]=x[i][j];
        return *this;
    }
    const int* operator[](int x) const { return a[x]; }
    int* operator[](int x) { return a[x]; }
    Mat operator*(const Mat& x) const // 带模矩阵乘法
    { // assert(col==x.lin);
        Mat ans;
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                for(int k = 0; k < 3; ++k)
                    ans[i][j] = add(ans[i][j], a[i][k] * (ll)x[k][j] % MODE);
        return ans;
    }
    Mat operator+=(const Mat& x)
    { // assert(col==x.lin);
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                a[i][j] = add(a[i][j], x[i][j]);
        return *this;
    }
    Mat operator-=(const Mat& x)
    { // assert(col==x.lin);
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                a[i][j] = add(a[i][j], MODE-x[i][j]);
        return *this;
    }
    Mat& operator*=(const Mat& x) { return *this = *this * x; }
    Mat& operator/=(const int x)
    {
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
                a[i][j]=a[i][j]*(ll)quick_pow(x,MODE-2)%MODE;
    }
    Mat operator^(ll ind) const // 快速幂
    { // assert(lin==col);
        Mat ans, base(*this);
        ans[0][0]=ans[1][1]=ans[2][2]=1;
        for(; ind; base *= base, ind >>= 1)
            if(ind & 1) ans *= base;
        return ans;
    }
    void print() const
    {
        for(int i=0;i<3||puts("");++i,puts(""))
            for(int j=0;j<3;++j)
                printf("%d ",a[i][j]);
    }
};

int num[MAXN],ans[MAXN];
pii query[MAXN];

int main()
{
    int n,a,q;
    scanf("%d %d %d",&n,&a,&q);
    Mat A,base1,base2,mul1,mul2;
    A[0][0]=a,A[0][2]=A[1][0]=A[2][2]=1;
    // (A^2).print();
    (A^5).print();
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num[i]),num[i]%=MODE;
        base1+=A^num[i];
        base2+=A^(2*num[i]%MODE);
    }
    // base1.print();
    // base2.print();
    for(int i=0;i<q;++i)
        scanf("%d",&query[i].first),query[i].second=i;
    sort(query,query+q);
    mul1=base1,mul2=base2;
    // ((mul1*mul1)-=mul2).print();
    pii pos;
    for(int i=1;i<=query[q-1].first;++i)
    {
        // mul1.print();
        // mul2.print();
        pos=*lower_bound(query,query+q,pii(i,0));
        debug2(mul1[0][1],mul1[0][2]);
        debug1(mul1[0][2]);
        if(pos.first==i)
            ans[pos.second]=mul1[0][2];
        mul1*=base1;
        mul1-=mul2;
        mul1/=n;
        // mul1.print();
        // mul2.print();
        if(i>=2) mul2*=base2;
    }
    for(int i=0;i<q;++i)
        printf("%d\n",ans[i]);
    return 0;
}