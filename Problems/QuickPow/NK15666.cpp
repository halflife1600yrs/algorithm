#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7;

int add(int x, int y)
{
    return (x += y) >= MODE ? x - MODE : x;
}

struct Mat
{
    int lin, col, **a;
    Mat(int l = 0, int c = 0) : lin(l), col(c)
    {
        a = new int*[lin];
        for(int i = 0; i < lin; ++i) a[i] = new int[col]();
    }
    Mat(const Mat& x) // 拷贝构造函数
    {
        lin = x.lin, col = x.col;
        a = new int*[lin];
        for(int i = 0, j; i < lin; ++i)
            for(a[i] = new int[col], j = 0; j < col; ++j)
                a[i][j] = x[i][j];
    }
    ~Mat() // 析构函数
    {
        for(int i = 0; i < lin; ++i) delete[] a[i];
        delete[] a;
    }
    const int* operator[](int x) const { return a[x]; }
    int* operator[](int x) { return a[x]; }
    Mat& operator=(Mat x)
    {
        swap(a, x.a), swap(lin, x.lin), swap(col, x.col);
        return *this;
    }
    Mat operator*(const Mat& x) const // 带模矩阵乘法
    { // assert(col==x.lin);
        Mat ans(lin, x.col);
        for(int i = 0; i < lin; ++i)
            for(int j = 0; j < x.col; ++j)
                for(int k = 0; k < col; ++k)
                    ans[i][j] = add(ans[i][j], a[i][k] * (ll)x[k][j] % MODE);
        return ans;
    }
    Mat& operator*=(const Mat& x) { return *this = *this * x; }
    Mat operator^(ll ind) const // 快速幂
    { // assert(lin==col);
        Mat ans(lin, col), base(*this);
        for(int i = 0; i < lin; ++i) ans[i][i] = 1; // 单位阵
        for(; ind; base *= base, ind >>= 1)
            if(ind & 1) ans *= base;
        return ans;
    }
};

int main()
{
    Mat A(6,6),x0(6,1);
    x0[0][0]=1,x0[2][0]=8,x0[3][0]=4,x0[4][0]=2,x0[5][0]=1;
    for(int i=0;i<6;++i) A[0][i]=1;
    for(int i=2;i<6;++i) A[i][i]=A[i][5]=1;
    A[1][0]=1,A[2][3]=A[2][4]=3,A[3][4]=2;
    int T;
    scanf("%d",&T);
    ll n;
    while(T--)
    {
        scanf("%lld",&n);
        Mat B;
        if(n==1)
        {
            puts("1");
            continue;
        } else if(n==2) B=x0;
        else B=(A^(n-2))*x0;
        int ans=0;
        for(int i=0;i<6;++i) ans=add(ans,B[i][0]);
        printf("%d\n",ans);
    }
    return 0;
}