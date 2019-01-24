#include <bits/stdc++.h>

#define debug(x) cout<<#x" = "<<x<<endl;
using namespace std;

const int mode = 1e9 + 7;
const int sz = 40000;
typedef long long ll;
int phi[sz] = {},pri[sz];
int num_pri = 0;

ll QuickPow(int x,int k)
{
	ll ans = 1,tmp = x;
	while(k)
	{
		if(k & 1) ans = ans * tmp%mode;
		tmp = tmp * tmp%mode;
		k >>= 1;
	}
	return ans;
}

ll inv(int x)
{
	return QuickPow(x,mode - 2);
}

ll dp(int colour,int lenz)        //将colour种颜色填到lenz个点的环上
{
	if(lenz == 1) return colour;
	ll ans = QuickPow(colour - 1,lenz);
	if(lenz & 1) ans = (ans - colour + 1 + mode) % mode;
	else ans = (ans + colour - 1) % mode;
	return ans;
}

ll GetPhi(int x)
{
	if(x < sz) return phi[x];
	int num = 0;
	ll ans = x;
	while(pri[num] <= x)
	{
		if(x%pri[num] == 0)
		{
			ans -= ans/pri[num];
			while(x%pri[num]==0)
				x /= pri[num];
		}
		num++;
	}
	return ans;
}

int main()
{
	for(int i = 2;i < sz;i++)
	{
		if(!phi[i]) { phi[i] = i - 1;pri[num_pri++] = i; }
		for(int j = 0;j <= num_pri && i*pri[j] < sz;j++)
		{
			if(i%pri[j] == 0)
			{
				phi[i*pri[j]] = phi[i] * pri[j];
				break;
			}
			else phi[i*pri[j]] = phi[i] * (pri[j] - 1);
		}
	}
	int lenz,colour;
	while(~scanf("%d %d",&lenz,&colour))
	{
		colour--;        //考虑中间的一个点
		ll ans = 0;
		for(int i = 2;i*i <= lenz;i++)  if(lenz%i == 0)
			if(i*i == lenz)
				ans = (ans + dp(colour,i)*phi[i] % mode) % mode;
			else
			{
				ans = (ans + dp(colour,i)*GetPhi(lenz / i) % mode) % mode;
				ans = (ans + dp(colour,lenz / i)*phi[i] % mode) % mode;
			}
		ans = (ans + dp(colour,lenz)) % mode * (colour + 1) % mode;
		ans = ans * inv(lenz) % mode;
		printf("%lld\n",ans);
	}
	return 0;
}

/*=======================================
added at 2018年9月12日 14:12:40	problem:HDU2865
对于一个顺时针旋转k个格子的置换,其一个循环的长度为n/gcd(n,k)
由于不能有颜色连续出现,k>=2且gcd>2
那么对gcd从2到n的情况进行计算,每次可以将所有gcd相同的情况相加
每种情况中,每个循环有gcd种,那么每种置换的不动点数量为dp[k][phi[gcd]+1]
dp[i][j]为将i种颜色填到j个空格的链上,头尾颜色相同且相邻颜色不同的方法数
对于环上情况j加一
状态转移方程为dp[i][j]=dp[i][j-1]*(i-2)+dp[i][j-2]*(i-1)
解得dp[i][j]=(i-1)^(j-1)+(i-1)*(-1)^(j-1)
取模减法一定要先+mode
=======================================*/