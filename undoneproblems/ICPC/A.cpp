#include <bits/stdc++.h>
#define ui unsigned long long
using namespace std;
int n, p, q, m;
unsigned int SA, SB, SC;
unsigned int rng61()
{
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
ui cnt, ans;
struct op
{
    ui num, mx;
};
stack<op> Q;
void PUSH(ui x, ui now)
{
    cnt = max(cnt, x);
    Q.push((op){ x, cnt });
    ans ^= Q.top().mx * now;
}
void POP(ui now)
{
    if(Q.empty())
    {
        ans ^= 0;
        cnt = 0;
        return;
    }
    Q.pop();
    if(Q.empty())
    {
        ans ^= 0;
        cnt = 0;
        return;
    }
    ans ^= Q.top().mx * now;
    cnt = Q.top().mx;
}
void gen()
{
    scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
    for(int i = 1; i <= n; i++)
    {
        if(rng61() % (p + q) < p)
            PUSH(rng61() % m + 1, i);
        else
            POP(i);
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++)
    {
        cnt = ans = 0;
        while(!Q.empty())
            Q.pop();
        gen();
        printf("Case #%d: %llu\n", i, ans);
    }
    return 0;
}