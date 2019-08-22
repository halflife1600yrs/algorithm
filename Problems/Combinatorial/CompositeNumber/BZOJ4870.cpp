#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n, mod, k, r;

int add(int x, int y)
{
    return (x += y) >= mod ? x - mod : x;
}

struct Mat
{
    int lin, col;
    int** a;
    Mat(int l = 0, int c = 0)
        : lin(l), col(c)
    {
        a = new int*[lin];
        for(int i = 0; i < lin; ++i) a[i] = new int[col]();
    }
    Mat(const Mat& x)
    { // 拷贝构造函数
        lin = x.lin, col = x.col;
        a = new int*[lin];
        for(int i = 0, j; i < lin; ++i)
            for(a[i] = new int[col], j = 0; j < col; ++j)
                a[i][j] = x[i][j];
    }
    ~Mat()
    { // 析构函数
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
    Mat operator*(const Mat& x) const // 矩阵乘法
    { // assert(col==x.lin);
        Mat ans(lin, x.col);
        for(int i = 0; i < lin; ++i)
            for(int j = 0; j < x.col; ++j)
                for(int k = 0; k < col; ++k)
                    ans[i][j] = add(ans[i][j], a[i][k] * (ll)x[k][j] % mod);
        return ans;
    }
    Mat& operator*=(const Mat& x) { return *this = *this * x; }
    Mat operator^(int ind) const // 快速幂
    { // assert(lin==col);
        if(!ind) return Mat(lin, col);
        Mat ans(*this), base(*this);
        --ind;
        while(ind)
        {
            if(ind & 1) ans *= base;
            base *= base;
            ind >>= 1;
        }
        return ans;
    }
};

int C[55][55]; // C[a][b] choose b from a

void init()
{
    for(int i = 0; i <= k; ++i) C[i][0] = C[i][i] = 1;
    for(int i = 1; i <= k; ++i)
        for(int j = 1; j < i; ++j)
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
}

int main()
{
    scanf("%d %d %d %d", &n, &mod, &k, &r);
    init();
    Mat A(k, k), x0(k, 1);
    for(int i = 1; i < k; ++i) x0[i][0] = C[k][i];
    x0[0][0] = 2; // 模k=0和k放在一个格子
    for(int i = 0; i < k; ++i)
        for(int j = 0, x = i; j < k; ++j, x = (x - 1 + k) % k)
        {
            if(x == 0)
                A[i][j] = 2;
            else
                A[i][j] = C[k][x];
        }
    x0 = (A ^ (n - 1)) * x0;
    printf("%d\n", x0[r][0]);
    return 0;
}

/*==================================================================
added at 2019-08-20 22:03:58 BZOJ4870
范德蒙德恒等式+矩阵快速幂
重构了一遍矩阵运算的板子
第二道用矩阵算组合数的题目
==================================================================*/