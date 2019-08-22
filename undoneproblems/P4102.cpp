#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=105,MODE=1e9+7;

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
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
    Mat operator*(ll x) const
    {
        Mat ans(*this);
        ans*=x;
        return ans;
    }
    Mat& operator*=(ll x)
    {
        for(int i=0;i<lin;++i)
            for(int j=0;j<col;++j)
                a[i][j]=(a[i][j]*x)%MODE;
        return *this;
    }
    Mat& operator+=(const Mat& x)
    {
        for(int i=0;i<lin;++i)
            for(int j=0;j<col;++j)
                a[i][j]=add(a[i][j],x[i][j]);
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

Mat land,A,B,C;
int v,e,k,q;

void work()
{
    Mat r(3,3),D,E,F;
    r[0][0]=r[0][2]=r[1][1]=r[1][2]=r[2][2]=1;
    r[0][1]=2;
    A=B=C=land;
    B*=2;
    while(k)
    {
        if(k&1)
        {

        }
        D=A*land,E=B*land,F=C*land;
        A+=D*r[0][0];
        (B+=D*r[0][1])+=E*r[1][1];
        ((C+=D*r[0][2])+=E*r[1][2])+=F*r[2][2];
        land*=land;
        r*=r;
        k>>=1;
    }
}

int main()
{
    // (A^2).print();
    scanf("%d %d %d %d",&v,&e,&k,&q);
    land=Mat(v,v);
    int fr,to;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        ++land[fr][to];
    }
    work();
    for(int i=0;i<q;++i)
    {
        scanf("%d %d",&fr,&to);

    }
    return 0;
}