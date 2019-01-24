#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mode = 1e9 + 7;
const int sz = 4;
typedef struct Matrix
{
	int y,x;
	ll cntnt[sz][sz];
    Matrix(int b,int a):y(b),x(a){}
	void setE()
	{
		for(int i = 0;i < y;i++)
			for(int j = 0;j < x;j++)
				if(i != j) cntnt[i][j] = 0;
				else cntnt[i][j] = 1;
	}
}Matrix;

void printm(Matrix* aim)
{
	for(int i = 0;i < aim->y;i++)
	{
		for(int j = 0;j < aim->x - 1;j++)
			printf("%d ",aim->cntnt[i][j]);
		printf("%d\n",aim->cntnt[i][aim->x - 1]);
	}
}

Matrix multi_mar(Matrix a,Matrix b)
{
	Matrix ans(a.y,b.x);
	int stan = a.x;
	for(int i = 0;i < a.y;i++)
		for(int j = 0;j < b.x;j++)
			for(int k = 0;k < stan;k++)
			{
                ans.cntnt[i][j] = (ans.cntnt[i][j] + 1ll * a.cntnt[i][k] * b.cntnt[k][j] % mode) % mode;
            }
	return ans;
}

Matrix quick_pow(Matrix aim,int powr)
{
    Matrix ans(aim.y,aim.x);
    ans.setE();
    while(powr)
    {
        if(powr & 1)
            ans = multi_mar(ans, aim);
        aim = multi_mar(aim, aim);
        powr >>= 1;
	}
	return ans;
}

int main()
{
    int cas, n;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &n);
        if(n==1)
        else if(n==2)
        else if(n==3)
        else if(n==4)
        else
        {
            Matrix mul(4,4);
            Matrix start(4, 1);
            mul.cntnt = { { 3, -2, -1, 0 }, { 1, 0, 0, 0 }, { 0, 1, 0, -3 }, { 0, 0, 1, 0 } };
            start.cntnt = { { 20, 9, 3, 1 } };
            quick_pow(mul, n - 3);
            multi_mar(mul, start);
        }
    }
}