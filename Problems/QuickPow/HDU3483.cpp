#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int mode=0;
const int sz = 53;
ll dp[sz][sz];
typedef struct Matrix
{
	int y,x;
	int cntnt[sz][sz];
	int loc;
	void setE()
	{
		for(int i = 0;i < y;i++)
			for(int j = 0;j < x;j++)
				if(i != j) cntnt[i][j] = 0;
				else cntnt[i][j] = 1;
	}
}Matrix;
Matrix area[20];
int occ[20];

void printm(Matrix* aim)
{
#ifdef DEBUG
	cout << "y=" << aim->y << " x=" << aim->x << endl;
#endif // DEBUG

	for(int i = 0;i < aim->y;i++)
	{
		for(int j = 0;j < aim->x - 1;j++)
			printf("%d ",aim->cntnt[i][j]);
		printf("%d\n",aim->cntnt[i][aim->x - 1]);
	}
}

void get_space(Matrix* &aim,int y,int x)
{
	for(int i = 0;i<20;i++)
		if(!occ[i])
		{
			occ[i] = 1;
			aim = &area[i];
			aim->loc = i,aim->y = y,aim->x = x;
			return;
		}
	aim = NULL;
}

int multi_mar(Matrix* &a,Matrix* b)
{
	Matrix* ans = NULL;
	get_space(ans,a->y,b->x);
	memset(ans->cntnt,0,sizeof(ans->cntnt));
	int stan = a->x;
	for(int i = 0;i < a->y;i++)
		for(int j = 0;j < b->x;j++)
			for(int k = 0;k < stan;k++)
			{
				ans->cntnt[i][j] = (ans->cntnt[i][j] + 1ll * a->cntnt[i][k] * b->cntnt[k][j]) % mode;
			}
	occ[a->loc] = 0;
	a = ans;
	return 0;
}

Matrix* quick_pow(Matrix* aim,int powr)
{
	Matrix* ans = NULL;
	get_space(ans,aim->y,aim->x);
	ans->setE();
	while(powr)
	{
		if(powr & 1)
			multi_mar(ans,aim);
		multi_mar(aim,aim);
		powr >>= 1;
	}
	return ans;
}

int main()
{
	memset(dp,0,sizeof(dp));
	for(int i = 0;i < sz;i++)
		dp[i][0] = 1;
	for(int i = 1;i <= 30;i++)
		for(int j = 1;j <= i;j++)
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
	int n,x;
	while(scanf("%d%d%d",&n,&x,&mode))
	{
		if(n == -1 && x == -1 && mode == -1) break;
		for(int i = 31;i < sz;i++)
			for(int j = 1;j <= i;j++)
				dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1])%mode;
		memset(occ,0,sizeof(occ));
		Matrix* pa = NULL;
		get_space(pa,x + 2,x + 2);
		memset(pa->cntnt,0,sizeof(pa->cntnt));
		Matrix* start = NULL;
		get_space(start,x + 2,1);
		for(int i = 0;i < x+2;i++)
		{
			for(int j = i;j <x+1;j++)
				pa->cntnt[i][j] = (x*(dp[x - i][x - j]) % mode) % mode;
			start->cntnt[i][0]=x,pa->cntnt[i][x + 1] = 1;
		}
		Matrix* ans = quick_pow(pa,n-1);
		multi_mar(ans,start);
		printf("%d\n",ans->cntnt[0][0]);
	}
	return 0;
}
/*======================
可以说为我们通过矩阵快速幂计算提供了很好的范例
同时也可以用相同的思路解决二项式展开中加入其他变量的问题
======================*/