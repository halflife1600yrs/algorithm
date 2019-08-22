#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N = 505;
const int M = 5;
typedef long long LL;
const LL mo = 998244353;

int n,m;
char s[N];

struct data{
    LL a[M][M];
    data operator * (const data &B)
    {
        data c; memset(c.a,0,sizeof(c.a));
        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    c.a[i][j] += a[i][k] * B.a[k][j];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                c.a[i][j] %= mo;
        return c;
    }
    data operator += (const data &B)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
            {
                a[i][j] += B.a[i][j];
                if (a[i][j] >= mo) a[i][j] -= mo;
            }
    }
}D[N][N],mi[10],g[N];

data ksm(data &k)
{
    k = k * k; data ret = k;
    k = k * k; k = k * k; ret = ret * k;
    return ret;
}

int main()
{
    scanf("%s",s + 1); cin >> m;
    n = strlen(s + 1); for (int i = 1; i <= n; i++) s[i] -= '0';
    for (int i = 1; i < m; i++) mi[1].a[i][i - 1] = 1;
    for (int i = 0; i < m; i++) mi[1].a[i][m - 1] = g[0].a[i][i] = 1;
    for (int i = 2; i < 10; i++) mi[i] = mi[i - 1] * mi[1];
    for (int i = 1; i <= n; i++)
    {
        data now; memset(now.a,0,sizeof(now.a));
        for (int j = 0; j < m; j++) now.a[j][j] = 1;
        for (int j = i; j <= n; j++)
        {
            now = ksm(now);
            if (s[j] > 0) now = now * mi[s[j]];
            D[i][j] = now;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = i - 1; j >= 0; j--)
            g[i] += g[j] * D[j + 1][i];
    LL Ans = 0;
    for (int i = 0; i < m; i++) Ans += g[n].a[0][i];
    cout << Ans % mo << endl;
    return 0;
}