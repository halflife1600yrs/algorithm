#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mode = 1e9 + 7;

int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b,a%b);
}

ll quick_pow(int x,int k)
{
	ll ans = 1,tmp = x;
	while(k)
	{
		if(k & 1) ans = ans * tmp % mode;
		tmp = tmp * tmp % mode;
		k >>= 1;
	}
	return ans;
}

ll inv(int x,int mode)
{
	return quick_pow(x,mode - 2);
}

int main()
{
	int cas,n,m;
	scanf("%d", &cas);		//n为颜色，m为环的长度
	for(int time = 0;time < cas;time++)
	{
		scanf("%d %d",&n,&m);
		ll ans = 0;
		for(int i = 0;i < m;i++)
			ans = (ans + quick_pow(n,gcd(m,i))) % mode;
		if(m & 1) ans = (ans + quick_pow(n,(m + 1) >> 1) * m % mode) % mode;
		else ans = (ans + ((quick_pow(n,1 + (m >> 1)) + quick_pow(n,m >> 1)) % mode) * (m >> 1) % mode) % mode;
		ans = ans * inv(m<<1,mode) % mode;
		printf("Case #%d: %lld\n",time+1,ans);
	}
    return 0;
}

