#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int sz = 1e4 + 5;
ll happy[sz],circle[2 * sz],quee[2 * sz],oper[2 * sz];

int gcd(int a,int b)
{
	if(!b) return a;
	else return gcd(b,a%b);
}

ll getmaxsub(ll* circle,int lenz,int sublenz)	//找到最大连续字串和
{
	int n,k,i,j;
	ll ans;
	n = lenz + sublenz - 1,k = sublenz;
	oper[1] = circle[1];
	ans = oper[1];
	int fre = 0,rea = 0;
	quee[rea++] = 1;
	for(i = 2;i <= n;i++)
	{
		oper[i] = circle[i];
		while(i - quee[fre] >= k)
		{
			fre++;
		}
		for(j = fre;j<rea;j++)
		{
			oper[quee[j]] += oper[i];
		}
		while(rea>fre && oper[quee[rea - 1]] <= oper[i])
		{
			rea--;
		}
		quee[rea++] = i;
		ans = max(ans,oper[quee[fre]]);
	}
	return ans;
}

int main()
{
	int cas,n,m,k;	//n是圈的长度，s是目标值，m是能量点，k是步长
	ll s;
	scanf("%d",&cas);
	for(int time = 1;time <= cas;time++)
	{
		scanf("%d %lld %d %d",&n,&s,&m,&k);
		for(int i = 0;i < n;i++)
			scanf("%lld",&happy[i]);
		int kind = gcd(n,k),lenz = n / kind,start;	//kind是循环数量，lenz是循环长度
		ll maxcir = m / lenz;
		ll ans = 0,sum,maxi;	//ans是总的答案，maxi是当此的最大连续字串和
		for(int i = 0;i < kind;i++)
		{
			maxi = 0,start = i,sum = 0;
			for(int j = 1;j <= lenz;j++)
			{
				int tmp = happy[(start + j * k) % n];
				circle[lenz + j] = circle[j] = tmp;
				sum += tmp;
			}
			ll maxsub1 = getmaxsub(circle,lenz,lenz),maxsub2 = getmaxsub(circle,lenz,m - maxcir * lenz);
			if(sum <= 0) maxi = maxsub1;
			else
			{
				ll needcir = s / sum;
				if(needcir >= maxcir)
				{
					ll a = maxsub1 + (maxcir - 1)*sum;
					ll b = maxsub2 + maxcir * sum;
					maxi = max(a,b);
				}
				if(needcir < maxcir)
					maxi = s;
			}
			if(maxi > ans || !i) ans = maxi;
		}
		if(ans >= s) ans = 0;
		else ans = s - ans;
		printf("Case #%d: %lld\n",time,ans);
	}
	return 0;
}

/*=======================================
added at 2018年9月12日 14:10:26	problem:HDU6444
ccpc1007(18)
主要问题是求数列中长度不超过k的最大连续子串
=======================================*/