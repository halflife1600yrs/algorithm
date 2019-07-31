#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;
const int sz = 100005;
P arry[sz];
int n, m;
struct DividingTree
{
    P data[22][sz];
    int toleft[22][sz];
    void build(int fr = 0, int to = n, int depth = 0)
    {
        if(to - fr == 1) return;
        int mid = (fr + to) / 2;
        int a = fr, b = mid;
        for(int i = fr; i < to; i++)
        {
            toleft[depth][i] = i > fr ? toleft[depth][i - 1] : 0;
            if(data[depth][i].second < mid) //
            {
                data[depth + 1][a++] = data[depth][i];
                toleft[depth][i]++;
            } else
                data[depth + 1][b++] = data[depth][i];
        }
        build(fr, mid, depth + 1);
        build(mid, to, depth + 1);
    }
    int find(int fr, int to, int k, int l = 0, int r = n, int depth = 0)
    { // 前闭后开区间
        if(to - fr == 1) return data[depth][fr].first;
        int mid = (l + r) / 2, prefix = fr > l ? toleft[depth][fr - 1] : 0;
        int left = toleft[depth][to - 1] - prefix;
        if(left >= k)
            find(l + prefix, l + prefix + left, k, l, mid, depth + 1);
        else
            find(mid + fr - l - prefix, mid + fr - l - prefix + to - fr - left, k - left, mid, r, depth + 1);
    }
} dtree;

bool cmp(P a, P b)
{
    return a.first < b.first;
}

int main()
{
    int cas;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &arry[i].first);
            arry[i].second = i;
        }
        sort(arry, arry + n, cmp);
        for(int i = 0; i < n; i++)
        {
            int tmp = arry[i].second;
            dtree.data[0][tmp] = { arry[i].first, i };
        }
        dtree.build();
        int a, b, c;
        for(int i = 0; i < m; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            printf("%d\n", dtree.find(a - 1, b, c));
        }
    }
    return 0;
}

/*=======================================
added at 2018年11月23日 21:13:18	problem:HDU2665
划分树模板
需要寻找第k大或是第k小时只需改变cmp的比较符号
注意英文的kth big是第k小的数
建树过程还需要重新修改，现在的方法空间会比较大（时间不清楚）
=======================================*/