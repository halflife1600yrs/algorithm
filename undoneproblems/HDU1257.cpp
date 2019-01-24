#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int a[sz];
int sdk[sz], top;

int b_srch(int x)
{ //递减数组
    //6 3 搜4
    //二分查找第一个比x小的数
    int fr = 0, to = top;
    while(to - fr > 1)
    {
        if(sdk[fr] == x) return fr;
        if(sdk[to - 1] == x) return to - 1;
        int mid = (fr + to) / 2;
        if(sdk[mid] == x)
            return mid;
        else if(sdk[mid] < x)
            to = mid;
        else
            fr = mid;
    }
    if(sdk[fr] < x)
        return fr;
    else
        return fr + 1;
}

int LIS(int* a, int lenz)
{
    top = 1;
    sdk[0] = a[0];
    for(int i = 1; i < lenz; ++i)
    {
        if(a[i] < sdk[top - 1])
            sdk[top++] = a[i];
        else if(a[i] > sdk[top - 1])
            sdk[b_srch(a[i])] = a[i];
    }
    for(int i = 0; i < top; ++i) printf("%d ", sdk[i]);
    printf("\n");
    return top;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        printf("%d\n", LIS(a, n));
    }
    return 0;
}

/*=======================================
added at 2019年Jan19日 15:44:30	problem:HDU1257
最长下降子序列-动态规划
朴素算法是O(n^2)
dp[i]表示以a[i]结尾的LIS长度
则dp[i]=max{dp[j]+1 (a[j]>a[i])}
这个十分简单,但每次都需要查找dp[1]->dp[n-1]
我们通过贪心性质来优化解法
当我们在数组末尾加入一个数x时,以它为结尾的LIS就相当于
在原数组中以某一个大于x+1的数为结尾的最长的LIS后接上x得到的序列
观察之后发现我们在原数组之中需要寻找的这个LIS是具有重叠的
比如
9 7 5 3 1 (x)
x为6时,它接在7后得到9 7 6
x为4时,它接在5后得到9 7 5 4
这两个序列的前缀是相同的
对于
=======================================*/