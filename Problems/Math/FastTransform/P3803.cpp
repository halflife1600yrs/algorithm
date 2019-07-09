#include <bits/stdc++.h>
const int sz = 2097155;
const double pi = acos(-1.0);
int ind;
struct Complex
{
    double real, i;
    Complex(double a = 0.0, double b = 0.0)
        : real(a), i(b){};
    void set_theta(double angle) { real = cos(angle), i = sin(angle); }
    Complex operator+(Complex x)
    {
        return Complex(real + x.real, i + x.i);
    }
    Complex operator-(Complex x)
    {
        return Complex(real - x.real, i - x.i);
    }
    Complex operator*(Complex x)
    {
        return Complex(real * x.real - i * x.i, real * x.i + x.real * i);
    }
};
Complex val[sz], fun1[sz], fun2[sz];


int get_index(int x)
{
    int ans = 1;
    while(ans <= x) ans <<= 1;
    return ans;
}

void change(Complex* fun)
{
    for(int i = 1, j = ind >> 1; i < ind - 1; i++)
    {
        if(i < j) std::swap(fun[i], fun[j]);
        int add = ind >> 1;
        while(j & add) j -= add, add >>= 1;
        j += add;
    }
}

void transform(Complex* arr, int oper)
{
    change(arr);
    for(int i = 1; i < ind; i <<= 1)
    {
        Complex base, step;
        for(int j = 0; j < ind; j += (i << 1))
        {
            base.set_theta(0), step.set_theta(oper * pi / i);
            for(int k = 0; k < i; k++)
            {
                Complex x = arr[j + k], y = base * arr[j + k + i];
                arr[j + k] = x + y;
                arr[j + k + i] = x - y;
                base = step * base;
            }
        }
    }
    if(oper == -1)
        for(int i = 0; i < ind; i++) arr[i].real /= ind;
}

int main()
{
    int n, m;
    while(~scanf("%d %d", &n, &m))
    {
        ind = get_index(n + m);
        std::fill(fun1, fun1 + ind + 1, 0);
        std::fill(fun2, fun2 + ind + 1, 0);
        for(int i = 0; i <= n; i++) scanf("%lf", &fun1[i].real);
        for(int i = 0; i <= m; i++) scanf("%lf", &fun2[i].real);
        transform(fun1, 1);
        transform(fun2, 1);
        for(int i = 0; i < ind; i++) val[i] = fun1[i] * fun2[i];
        transform(val, -1);
        for(int i = 0; i < n + m; i++) printf("%d ", (int)(val[i].real + 0.5));
        printf("%d\n", (int)(val[n + m].real + 0.5));
    }
    return 0;
}

/*=======================================
added at 2018年10月12日 18:48:19	problem:P3803
fft模板
=======================================*/