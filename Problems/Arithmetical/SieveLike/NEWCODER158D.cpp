#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char sieve[20000003];
int pri[12000000];
int main()
{
    int a, n;
    while(~scanf("%d %d", &a, &n))
    {
        int num_pri = 0, kind = (n - 1) / a, ans = 0;
        memset(sieve, 0, sizeof(sieve));
        for(int i = 1; i <= kind; i++)
        {
            if(!sieve[i]) pri[num_pri++] = i;
            ll k = i * a + i + 1;
            for(int j = 0; j < num_pri && k <= kind; j++, k = i * pri[j] * a + i + pri[j])
            {
                if(sieve[k] != 2)
                    if(!sieve[i])
                        sieve[k] = 2, ans++;
                    else
                        sieve[k] = 1;
                if((i - pri[j]) % (a * pri[j] + 1) == 0) break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*=======================================
added at 2018年10月08日 15:33:02	problem:NEWCODER158D
(ax+1)*(bx+1)=abx^2+(a+b)x+1,系数为abx+a+b
对于系数为k的贝利弗斯数,它有系数为p1的贝利弗斯数作为因子的充要条件:
(k-p1)%(ap1+1)==0
4 1000 (110)
5 2000 (259)
在这种筛法下有可能出现一个数被筛多次
以及一个可能被表示为两个素数相乘的数被表示为多个数相乘然后不被计算
所以对已经为答案的数不再修改
所以使用欧拉筛做这题不是很好的方法
以上代码没过,以下为一个解法
const int maxn = 2e8;
typedef long long ll;
bool vis[maxn], vis2[maxn];
int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    ll a, n;
    scanf("%lld%lld", &a, &n);
    for(int i = 1; a * i + 1 <= n; i++)
        if(!vis[i])
        {
            for(int j = 1; (a * i + 1) * (a * j + 1) <= n; j++)
                vis[a * i * j + i + j] = 1;
        }
    int ans = 0;
    for(int i = 1; a * i + 1 <= n; i++)
        if(!vis[i])
        {
            for(int j = i; (a * i + 1) * (a * j + 1) <= n; j++)
                if(!vis[j])
                {
                    if(!vis2[a * i * j + i + j])
                    {
                        ans++;
                        vis2[a * i * j + i + j] = 1;
                    }
                }
        }
    printf("%d\n", ans);
}
=======================================*/