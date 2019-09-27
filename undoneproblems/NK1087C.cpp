#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE = 998244353;

inline int add(int a, int b)
{
    return (a += b) >= MODE ? a - MODE : a;
}

struct Mat
{
    int lin, col;
    ll** a;
    Mat(int l = 0, int c = 0)
        : lin(l), col(c)
    {
        a = new ll*[lin];
        for(int i = 0; i < lin; ++i) a[i] = new ll[col]();
    }
    Mat(const Mat& x) // 拷贝构造函数
    {
        lin = x.lin, col = x.col;
        a = new ll*[lin];
        for(int i = 0, j; i < lin; ++i)
            for(a[i] = new ll[col], j = 0; j < col; ++j)
                a[i][j] = x[i][j];
    }
    ~Mat() // 析构函数
    {
        for(int i = 0; i < lin; ++i) delete[] a[i];
        delete[] a;
    }
    const ll* operator[](int x) const { return a[x]; }
    ll* operator[](int x) { return a[x]; }
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
                    ans[i][j] = add(ans[i][j], a[i][k] * x[k][j] % MODE);
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
    void print() const
    {
        for(int i = 0; i < lin || (puts(""), 0); ++i, puts(""))
            for(int j = 0; j < col; ++j) printf("%d ", a[i][j]);
    }
};

int main()
{
    ll n;
    Mat A(4, 4);
    A[0][0] = A[0][1] = A[1][0] = A[2][0] = A[2][2] = A[2][3] = A[3][2] = 1;
    while(~scanf("%lld", &n))
        printf("%d\n", n ? (A ^ (n - 1))[2][0] : 0);
    return 0;
}