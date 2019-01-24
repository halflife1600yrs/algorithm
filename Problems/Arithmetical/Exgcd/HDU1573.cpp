#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll rema[15],mode[15];

ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b == 0) { x = 1;y = 0;return a; }
	ll t = exgcd(b,a % b,x,y);
	ll x0 = x,y0 = y;
	x = y0;y = x0 - (a / b) * y0;
	return t;
}


ll solve(int i,int j)
{
	ll m1 = mode[i],m2 = mode[j],r = rema[j] - rema[i];
	ll z1,z2;
	ll com = exgcd(m1,m2,z1,z2);
	if(r%com) return 0;
	else
		mode[j] = m1 / com * m2,rema[j] = (m1 / com *z1 * r + rema[i]) % mode[j];
	return 1;
}

int main()
{
	int cas,m;
	ll n,ans;
	scanf("%d",&cas);
	while (cas--)
	{
		scanf("%lld %d",&n,&m);
		for(int i = 0;i < m;i++)
			scanf("%lld",&mode[i]);
		for(int i = 0;i < m;i++)
			scanf("%lld",&rema[i]);
		int flag = 1;
		for(int i = 0;i < m - 1;i++)
			if(!solve(i,i + 1)) { flag = 0;break; }
		if(flag)
		{
			rema[m - 1] = (rema[m - 1] + mode[m - 1]) % mode[m - 1];
			if(n < rema[m - 1]) printf("0\n");
			else
			{
				ans = (n - rema[m - 1]) / mode[m - 1] + 1;
				if(ans && !rema[m - 1]) ans--;
				printf("%lld\n",ans);
			}
		}
		else printf("0\n");
	}
    return 0;
}

/*=======================================
added at 2018年9月12日 14:13:14	problem:HDU1573
解线性同余方程组模板

扩展gcd:计算ax+by=gcd(a,b)的解
扩展gcd在计算负数时会出错,不过我们只需要计算m1z1-m2z2=r2-r1中一个满足条件的z1值
此时m2为正或负都是可以得出正确解的,直接取绝对值即可
!!!注意题目中需要求的是正整数因此需要判0!!!
=======================================*/