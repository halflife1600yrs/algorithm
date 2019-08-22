#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=505,MODE=998244353;
int m;

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

struct Mat
{
    int lin, col,**a;
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
    Mat& operator+=(const Mat& x)
    { // assert(lin==x.lin&&col==x.col);
        for(int i=0;i<lin;++i)
            for(int j=0;j<col;++j)
                a[i][j]=add(a[i][j],x[i][j]);
        return *this;
    }
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
        for(int i=0;i<lin||puts("");++i,puts(""))
            for(int j=0;j<col;++j) printf("%d ",a[i][j]);
    }
};

Mat dp[MAXN][MAXN],multi[10],ans[MAXN];
char str[MAXN];

int main()
{
    int m,L;
    scanf("%s %d",str,&m);
    L=strlen(str);
    Mat A(m,m);
    for(int i=0;i<m-1;++i) A[0][i]=A[i+1][i]=1;
    A[0][m-1]=1;
    multi[0]=A^0;
    for(int i=1;i<10;++i) multi[i]=multi[i-1]*A;
    for(int i=0;i<L;++i) dp[i][i]=multi[(int)str[i]-'0'];
    for(int i=0;i<L-1;++i)
        for(int j=i+1;j<L;++j)
            dp[i][j]=(dp[i][j-1]^10)*dp[j][j];
    for(int i=0;i<L;++i)
    {
        ans[i]=dp[0][i];
        for(int j=0;j<i;++j)
            ans[i]+=ans[j]*dp[j+1][i];
    }
    int sum=ans[L-1][0][0];
    printf("%d\n",sum);
    return 0;
}
/*==================================================================
added at 2019-08-06 22:07:02	P3176
3513541 5
==================================================================*/
/*==================================================================
added at 2019-08-21 19:57:26 P3176
优化了快速幂板子之后重写
考虑:
1. 一个数分割成若干个数字,求它们的和?
- 用dp[i][j]表示第i位到第j位作为连续的一段的和
    f[i]表示正好在第i位割一刀,前面所有可能方案的和;
    枚举f[i]前一刀在j这个位置,再加上dp[j+1][i]这一段变化而来,n^2求解;
2. 一个数分割成若干个数字,求它们对x的指数的和?
    跟上一个问题其实差不多,只不过变成乘以dp[j+1][i]
这题其实就是把x变成一个矩阵,这个矩阵是(一个数拆分为小于等于m的数)的递推矩阵
==================================================================*/