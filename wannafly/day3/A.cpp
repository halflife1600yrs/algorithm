#include <bits/stdc++.h>

using namespace std;

bool state[11];
double number[10];
int ok;

bool check(int lenz, double* n)
{
    if(lenz == 1)
    {
        if(n[0] == 24)
            return 1;
        else
            return 0;
    }
    double tmp[10];
    for(int i = 0; i < lenz - 1; ++i)
    {
        for(int j = i + 1; j < lenz; ++j)
        {
            int top = 0;
            for(int k = 0; k < lenz; ++k)
            {
                if(n[k] == 24) return 1;
                if(k != i && k != j)
                {
                    tmp[top++] = n[k];

                }
            }
            double a = n[i], b = n[j];
            tmp[top] = a + b;
            if(check(lenz - 1, tmp)) return 1;
            tmp[top] = a * b;
            if(check(lenz - 1, tmp)) return 1;
            tmp[top] = a - b;
            if(check(lenz - 1, tmp)) return 1;
            tmp[top] = b - a;
            if(check(lenz - 1, tmp)) return 1;
            tmp[top] = b / a;
            if(check(lenz - 1, tmp)) return 1;
            tmp[top] = a / b;
            if(check(lenz - 1, tmp)) return 1;
        }
    }
    return 0;
}

void generate(int num, int x)
{
    if(num > 7) return;
    if(x > 10)
    {
        int top = 0;
        for(int i = 1; i <= 10; ++i)
            if(state[i])
                number[top++] = i;
        if(check(top, number))
        {
            for(int i = 1; i <= 10; ++i)
                if(state[x]) printf("%d ", i);
            printf("\n");
        }
        return;
    }
    state[x] = 1;
    generate(num + 1, x + 1);
    state[x] = 0;
    generate(num, x + 1);
    return;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    printf("32\n");
    ok = 0;
    generate(0, 1);
    system("pause");
    return 0;
}

/*=======================================
added at 2019年Jan22日 14:04:29	problem:A
4、6
3、8
2、3、4

=======================================*/