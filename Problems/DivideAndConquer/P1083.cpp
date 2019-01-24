#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int sz = 1e6 + 5;
int n, m;
ll clsrm[sz], used[sz], sum[sz];
struct Need
{
    int d, s, e;
    void set() { scanf("%d %d %d", &d, &s, &e), ++e; }
} needs[sz];
void mark(int fr, int to)
{ //将[1,fr)调整为[1,to)
    if(to > fr)
    {
        for(int i = fr; i < to; ++i)
            used[needs[i].s] += needs[i].d, used[needs[i].e] -= needs[i].d;
    } else
    {
        for(int i = fr - 1; i >= to; --i)
            used[needs[i].s] -= needs[i].d, used[needs[i].e] += needs[i].d;
    }
}
int check(int aim)
{
    sum[1] = used[1];
    bool perfect = 1;
    for(int i = 2; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + used[i];
        if(clsrm[i] < sum[i])
            return -1;
        else if(clsrm[i] == sum[i])
            perfect = 0;
    }
    return perfect;
}
int main()
{
    while(~scanf("%d %d", &n, &m))
    {
        for(int i = 1; i <= n; ++i) scanf("%lld", &clsrm[i]);
        for(int i = 0; i < m; ++i) needs[i].set();
        int fr = 0, to = m + 1, mid = 0, status;
        if(m == 1)
        {
            int ans = 0;
            for(int i = needs[0].s; i < needs[0].e; ++i)
                if(clsrm[i] < needs[0].d) ans = -1;
            if(ans == -1)
                printf("-1\n1\n");
            else
                printf("0\n");
            continue;
        }
        memset(used, 0, sizeof(used));
        while(to - fr > 1)
        {
            mark(mid, (fr + to) / 2);
            mid = (fr + to) / 2;
            status = check(mid);
            if(status >= 0)
                fr = mid;
            else
                to = mid;
        }
        if(status >= 0)
        {
            if(mid == m)
                printf("0\n");
            else
                printf("-1\n%d\n", mid + 1);
        } else
            printf("-1\n%d\n", mid);
    }
    return 0;
}

/*=======================================
added at 2018年12月31日 12:00:06	problem:P1083
二分答案+差分
对于二分还是有很多地方容易出错，特别是区间的开闭问题上
1、需要注意的是二分时的区间必须完全包含答案可能存在的所有范围
比如该题目虽然只有m个申请，也就是说标号从0开始，区间是[0,m)
但是有可能教室满足所有申请，此时相当于拒绝第m+1个申请
因此区间应当选择[0,m+1)
2、除非能够保证只有一个答案可以满足中间状态，否则不要在出现中间状态时break
比如这题，可能出现连续多个申请满足之后教室刚好分配完的状况
=======================================*/