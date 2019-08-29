#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV = 200, MODE = 1e9;
int V, E, graph[MAXV][MAXV], d[MAXV];

int Gauss()
{
    int ans = 1;
    for(int i = 1; i < V; ++i)
    {
        for(int j = i + 1; j < V; ++j)
            while(graph[j][i])
            {
                int t = graph[i][i] / graph[j][i], tmp;
                for(int k = i; k < V; k++)
                {
                    tmp = (graph[i][k] - t * (ll)graph[j][k]) % MODE;
                    graph[i][k] = graph[j][k];
                    graph[j][k] = tmp;
                }
                ans = MODE - ans;
            }
        ans = ans * (ll)graph[i][i] % MODE;
        if(ans < 0) ans += MODE;
    }
    return ans;
}

int num[15][15];
char str[15][15];
const int xx[4] = { 1, -1, 0, 0 }, yy[4] = { 0, 0, 1, -1 };

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        for(int j = 1; j <= m; ++j)
            if(str[i][j] == '.') num[i][j] = ++V;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if(num[i][j])
                for(int k = 0; k < 4; ++k)
                    if(num[i + xx[k]][j + yy[k]])
                        ++graph[num[i][j]][num[i][j]], --graph[num[i][j]][num[i + xx[k]][j + yy[k]]];
    printf("%d\n", Gauss());
    return 0;
}

/*==================================================================
added at 2019-08-28 20:33:41 P4208
矩阵树定理
注意辗转相除这里是不能每次变成正数的
==================================================================*/