#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n, x, mod;

ll add(ll x, ll y)
{
    return (x += y) >= mod ? x % mod : x;
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
    Mat(const Mat& x)
    { // 拷贝构造函数
        lin = x.lin, col = x.col;
        a = new ll*[lin];
        for(int i = 0, j; i < lin; ++i)
            for(a[i] = new ll[col], j = 0; j < col; ++j)
                a[i][j] = x[i][j];
    }
    ~Mat()
    { // 析构函数
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
    Mat operator*(const Mat& x) const // 矩阵乘法
    { // assert(col==x.lin);
        Mat ans(lin, x.col);
        for(int i = 0; i < lin; ++i)
            for(int j = 0; j < x.col; ++j)
                for(int k = 0; k < col; ++k)
                    ans[i][j] = add(ans[i][j], a[i][k] * x[k][j] % mod);
        return ans;
    }
    Mat& operator*=(const Mat& x) { return *this = *this * x; }
    Mat operator^(int ind) const // 快速幂
    { // assert(lin==col);
        Mat ans(lin, col), base(*this);
        for(int i = 0; i < lin; ++i) ans[i][i] = 1;
        for(; ind; base *= base, ind >>= 1)
            if(ind & 1) ans *= base;
        return ans;
    }
};

ll C[55][55]; // C[a][b] choose b from a

void init()
{
    for(int i = 0; i < 55; ++i) C[i][0] = C[i][i] = 1;
    for(int i = 1; i < 55; ++i)
        for(int j = 1; j < i; ++j)
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
}

int main()
{
    while(scanf("%d %d %d", &n, &x, &mod), mod >= 0)
    {
        init();
        Mat A(x + 2, x + 2), x0(x + 2, 1);
        for(int i = 0; i < x + 2; ++i) x0[i][0] = x;
        for(int i = 0; i < x + 1; ++i)
        {
            for(int j = x, k = x - i; k >= 0; --k, --j)
            {
                A[i][j] = C[x - i][k] * x % mod;
                if(!i) A[x + 1][j] = A[i][j];
            }
        }
        A[x + 1][x + 1] = 1;
        x0 = (A ^ (n - 1)) * x0;
        printf("%lld\n", x0[x + 1][0]);
    }
    return 0;
}
/*======================
可以说为我们通过矩阵快速幂计算提供了很好的范例
同时也可以用相同的思路解决二项式展开中加入其他变量的问题
======================*/
/*==================================================================
added at 2019-08-21 09:47:55 HDU3483
用优化了的板子重做这题
果然还是封装好舒服,虽然板子长但是最后代码短而且跑的也快一点
==================================================================*/