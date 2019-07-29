#include <bits/stdc++.h>

const int MAXN = 2097155;
const double pi = acos(-1.0);

struct Complex
{
    double real, i;
    Complex(double a = 0.0, double b = 0.0)
        : real(a), i(b){};
    void set_theta(double angle) { real = cos(angle), i = sin(angle); }
    Complex operator+(const Complex &x) const
    {
        return Complex(real + x.real, i + x.i);
    }
    Complex operator-(const Complex &x) const
    {
        return Complex(real - x.real, i - x.i);
    }
    Complex operator*(const Complex &x) const
    {
        return Complex(real * x.real - i * x.i, real * x.i + x.real * i);
    }
};
Complex val[MAXN], fun1[MAXN], fun2[MAXN];

int resort[MAXN],ind;
void init(int x)
{
    ind = 1;
    int l = 0;
    while (ind < x + 1)
        ind <<= 1, ++l;
    for (int i = 0; i < ind; i++)
        resort[i] = (resort[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

void transform(Complex *arr, int oper)
{
    for (int i = 1; i < ind; ++i)
        if (i < resort[i])
            std::swap(arr[i], arr[resort[i]]);
    Complex base, step, x, y;
    for (int i = 1; i < ind; i <<= 1)
    {
        step.set_theta(oper * pi / i);
        for (int j = 0; j < ind; j += (i << 1))
        {
            base = Complex(1.0, 0.0);
            for (int k = 0; k < i; k++)
            {
                x = arr[j + k], y = base * arr[j + k + i];
                arr[j + k] = x + y;
                arr[j + k + i] = x - y;
                base = step * base;
            }
        }
    }
    if (oper == -1)
        for (int i = 0; i < ind; ++i)
            arr[i].real /= ind;
}

void fft()
{
    transform(fun1, 1);
    transform(fun2, 1);
    for (int i = 0; i < ind; ++i)
        val[i] = fun1[i] * fun2[i];
    transform(val, -1);
}

int main()
{
    int n, m;
    while (~scanf("%d %d", &n, &m))
    {
        init(n + m);
        for (int i = 0; i <= n; ++i)
            scanf("%lf", &fun1[i].real), fun1[i].i = 0.0;
        for (int i = 0; i <= m; ++i)
            scanf("%lf", &fun2[i].real), fun2[i].i = 0.0;
        fft();
        for (int i = 0; i < n + m; ++i)
            printf("%d ", (int)round(val[i].real));
        printf("%d\n", (int)round(val[n + m].real));
    }
    return 0;
}

/*=======================================
added at 2018年10月12日 18:48:19	problem:P3803
fft模板
=======================================*/