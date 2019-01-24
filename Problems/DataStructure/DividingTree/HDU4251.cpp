#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int arry[sz];
int n;
struct DividingTree
{
    int data[22][sz], toleft[22][sz];
    void build(int fr = 0, int to = n, int depth = 0)
    {
        if(to - fr == 1) return;
        int mid = (fr + to) / 2;
        int suppose = 0;
        for(int i = mid - 1; i >= fr && arry[i] == arry[mid]; i--) suppose++;
        int a = fr, b = mid;
        for(int i = fr; i < to; i++)
        {
            int tmp = data[depth][i];
            toleft[depth][i] = i > fr ? toleft[depth][i - 1] : 0;
            if(tmp < arry[mid] || (tmp == arry[mid] && 0 < suppose--))
                data[depth + 1][a++] = tmp, toleft[depth][i]++;
            else if(tmp >= arry[mid])
                data[depth + 1][b++] = tmp;
        }
        build(fr, mid, depth + 1);
        build(mid, to, depth + 1);
    }
    int find(int l, int r, int k, int fr = 0, int to = n, int depth = 0)
    {
        if(r - l == 1) return data[depth][l];
        int mid = (fr + to) / 2;
        int prefix = l > fr ? toleft[depth][l - 1] : 0, left = toleft[depth][r - 1] - prefix;
        if(left >= k)
            find(fr + prefix, fr + prefix + left, k, fr, mid, depth + 1);
        else
            find(mid + (l - fr - prefix), mid + r - fr - toleft[depth][r - 1], k - left, mid, to, depth + 1);
    }
} dtree;

int main()
{
    int cas = 0, m;
    while(~scanf("%d", &n))
    {
        cas++;
        printf("Case %d:\n", cas);
        for(int i = 0; i < n; i++) scanf("%d", &arry[i]), dtree.data[0][i] = arry[i];
        sort(arry, arry + n);
        dtree.build();
        int a, b;
        scanf("%d", &m);
        for(int i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b);
            printf("%d\n", dtree.find(a - 1, b, (b - a) / 2 + 1));
        }
    }
    return 0;
}

/*=======================================
added at 2018年11月24日 18:59:29	problem:HDU4251
划分树模板题
优化了建树方法
=======================================*/