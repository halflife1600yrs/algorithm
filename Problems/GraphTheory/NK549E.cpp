#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=105,MODE=1e9+7;

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

int main()
{
    int v,e,k,s;
    scanf("%d %d %d %d",&v,&e,&k,&s);
    Mat land(v,v);
    int fr,to;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        --fr,--to;
        ++land[fr][to];
    }
    // land.print();
    land=land^k;
    int sum=0;
    --s;
    for(int i=0;i<v;++i)
        if(i!=s) sum=add(sum,land[s][i]);
    printf("%d\n",sum);
    return 0;
}

/*==================================================================
added at 2019-08-22 10:05:06 NK549E
在图上从i走到j恰好a步的方法等于邻接矩阵a次幂在(i,j)位置的值
==================================================================*/