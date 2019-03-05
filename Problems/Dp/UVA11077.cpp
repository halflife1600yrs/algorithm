#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int sz = 25;
ull dp[sz][sz] = {};	//dp[i][j]表示i个数最少需要j次交换的序列数

int main()
{
	//freopen("D:\\output.txt","w",stdout);
	memset(dp,0,sizeof(dp));
	for(int i = 1;i < sz;i++) dp[i][0] = 1;
	for(int i = 1;i < sz;i++)
		for(int j = 1;j < i;j++)
			dp[i][j] = dp[i - 1][j - 1] * (i - 1) + dp[i - 1][j];
	int n,k;	//n是长度，k是最少交换次数
	while(scanf("%d %d",&n,&k),n || k)
		printf("%llu\n",dp[n][k]);
    return 0;
}

/*======================
注意数据范围
提交时记得注释freopen
无序地将一个集合分成若干个给定大小的集合的数量应该是用类似的方法计算
对于有序的问题直接使用组合数即可
======================*/