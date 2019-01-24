#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define debug(x)    \
    cout << #x "="; \
    x.print();

int n, k, r;
typedef pair<int, double> Dis;
const int maxn = 105;
const int maxk = 55;
const double INF = 1e100;
const double range = 3e-6;
typedef struct Direct
{
    double pos[maxn];
    void print()
    {
        for(int i = 0; i < k - 1; i++) printf("%.5f ", pos[i] + range);
        printf("%.5f\n", pos[k - 1] + range);
    }
    double lenz()
    {
        double ans = 0;
        for(int i = 0; i < k; i++) ans += pos[i] * pos[i];
        return sqrt(ans);
    }
    Direct operator-(Direct& x)
    {
        Direct ans;
        for(int i = 0; i < k; i++) ans.pos[i] = pos[i] - x.pos[i];
        return ans;
    }
    void operator-=(Direct& x)
    {
        for(int i = 0; i < k; i++) pos[i] -= x.pos[i];
    }
    Direct operator+(Direct& x)
    {
        Direct ans;
        for(int i = 0; i < k; i++) ans.pos[i] = pos[i] + x.pos[i];
        return ans;
    }
    void operator+=(Direct& x)
    {
        for(int i = 0; i < k; i++) pos[i] += x.pos[i];
    }
    double operator*(Direct& x)
    {
        double ans = 0;
        for(int i = 0; i < k; i++) ans += pos[i] * x.pos[i];
        return ans;
    }
} Direct;
Direct operator*(double x, Direct& a)
{
    Direct ans;
    for(int i = 0; i < k; i++) ans.pos[i] = a.pos[i] * x;
    return ans;
}
Direct center, point, area, normal[maxk], base[maxk];
Dis dis[maxn];
double lenz[maxk];
bool cmp(Dis a, Dis b) { return a.second < b.second; }

double check(Direct x, int dim)
{
}

void solve(int dim)
{
    double l1 = point.lenz();
    for(int i = 0; i < dim - 1; i++)
    {
        int x = dis[i].first, y = dis[(i + 1) % dim].first;
        base[i].pos[x] = area.pos[x], base[i].pos[y] = -area.pos[y];
        lenz[i] = base[i] * base[i];
        for(int j = 0; j < i; j++)  //施密特正交化
            base[i] -= (base[i] * base[j] / lenz[j]) * base[i];
        normal += (l1 / sqrt(lenz[i])) * base[i];
        
    }
    for(int i = dim-2; i >=0; i--)
    {
        double l2 = normal * normal, tmp = check(point - (point * normal / l2) * normal, i);
        if(tmp == -1.0) return;
        ans = tmp;
        normal -= (l1 / sqrt(lenz[i])) * base[i];
    }
}

int main()
{
    int cas;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d%d%d", &n, &k, &r); //n点数-50,k维数-100
        for(int i = 0; i < k; i++) scanf("%lf", &center.pos[i]);
        memset(area.pos, 0, sizeof(area.pos));
        memset(base, 0, sizeof(base));
        for(int j = 0; j < n; j++)
        {
            int dim = 0; //表示最高需要考虑几维
            for(int i = 0; i < k; i++)
            {
                scanf("%lf", &point.pos[i]), point.pos[i] -= center.pos[i];
                if(point.pos[i]) dim++, area.pos[i] = point.pos[i] > 0 ? 1 : -1;
            }
            for(int i = 0; i < k; i++)
            {
                point.pos[i] -= area.pos[i];
                dis[i].first = i, dis[i].second = point.lenz();
                point.pos[i] += area.pos[i];
            }
            sort(dis, dis + k, cmp); //对最靠近的端点排序,然后贪心选择
            point.pos[dis[0].first] -= area.pos[dis[0].first]; //dis[0].first是最近的端点的维数序号
            solve(dim); //显然如果某个坐标为0,那么可以说该点只在一个更小的子空间,该端点不需要考虑
        }
    }
    return 0;
}

/*=======================================
added at 2018年9月25日 15:20:01	problem:beijingH

=======================================*/
/*=======================================
added at 2018年9月25日 21:46:14	problem:beijingH
好像低估这题了
=======================================*/
/*=======================================
added at 2018年9月27日 20:13:05	problem:beijingH
1
1 3
1
0 0 0
-19 21 21
高维空间需要判断法向量与另一向量是否在同一子空间
=======================================*/
