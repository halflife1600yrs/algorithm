#include <bits/stdc++.h>

using namespace std;

typedef struct Circle
{
    int x, y, r;
    double d1, d2;
} Circle;
const int sz = 1e3 + 5;
const double INF = 1e100;
int dis[sz][sz];
Circle circle[sz];
int n, a, b, c1, c2;
double base, ans[sz];

bool cmp(Circle x, Circle y)
{
    return x.d1 < y.d1;
}

inline double cir_to_line(Circle c, int z)
{
    return max(0.0, abs(a * c.x + b * c.y + z) / base - c.r);
}

inline double cir_to_cir(Circle c1, Circle c2)
{
    int x = c1.x - c2.x, y = c1.y - c2.y;
    return max(0.0, sqrt(x * x + y * y) - c1.r - c2.r);
}

int main()
{
    while(~scanf("%d %d %d %d %d", &n, &a, &b, &c1, &c2))
    {
        base = sqrt(a * a + b * b);
        double d = abs(c1 - c2) / base;
        for(int i = 0; i < n; i++)
        {
            scanf("%d %d %d", &circle[i].x, &circle[i].y, &circle[i].r);
            circle[i].d1 = cir_to_line(circle[i], c1), circle[i].d2 = cir_to_line(circle[i], c2);
            if(circle[i].d1 >= d || circle[i].d2 >= d)
            {
                i--, n--;
                continue;
            }
        }
        sort(circle, circle + n, cmp); //到l1的距离递增排序，后面的对前面的dp
        for(int i = 0; i < n; i++) //dp[x]=x.d2+max{dp[i]+dis(x,i)},i是x前面的圆
        {
            ans[i] = circle[i].d1;
            if(!ans[i]) continue;
            for(int j = 0; j < i; j++)
            {
                double tmp = ans[j] + cir_to_cir(circle[i], circle[j]);
                if(tmp < ans[i]) ans[i] = tmp;
            }
        }
        double mini = ans[0] + circle[0].d2;
        for(int i = 1; i < n; i++)
            if(ans[i] + circle[i].d2 < mini) mini = ans[i] + circle[i].d2;
        printf("%.6f\n", mini);
    }
    return 0;
}

/*=======================================
added at 2018年10月02日 14:24:28	problem:NEWCODER210L
居然1a了
刚开始以为是最短路
后来发现只要dp就行了,对于每个圆想要最好方案一定是取距离减少的圆
=======================================*/