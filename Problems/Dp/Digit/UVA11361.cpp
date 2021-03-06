#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll mode;
ll dp[11][90][90] = {};	//三维分别为长度，各位和模7，模7
ll lenz1,lenz2;

ll resolve(ll x,ll &lenz)
{
	lenz = 0;
	ll sum = 0;
	while(x)
	{
		sum += x % 10;
		x /= 10,lenz++;
	}
	return sum;
}

ll GetAns(ll x,ll sum,ll lenz)
{
	ll ans = 0,powr = 1,tmp = x;	//tmp用来计算每位数字(除10),x则是每次的范围(每次计算的位置上-1)
	if(sum%mode == 0 && x%mode == 0) ans++;
	for(ll i = 1;i <= lenz;i++)
	{
		for(ll num = tmp % 10 - 1;num >= 0;num--)
		{
			sum -= 1,x -= powr;
			ans += dp[i - 1][(mode - sum % mode) % mode][(mode - x % mode) % mode];
		}
		tmp /= 10,powr *= 10;
	}
	return ans;
}

int main()
{
	int cas;
	ll a,b;
	scanf("%d", &cas);
	while (cas--)
	{
		scanf("%lld %lld %lld",&a,&b,&mode);
		if(mode > 85) printf("0\n");
		else
		{
			ll sum1 = resolve(a-1,lenz1),sum2 = resolve(b,lenz2);
			memset(dp,0,sizeof(dp));
			dp[0][0][0] = 1;
			ll powr = 1;
			ll maxlenz = max(lenz1,lenz2);
			for(ll i = 1;i <= maxlenz;i++)
			{
				ll tmp;
				for(ll j = 0;j < mode;j++)		//目标各位和模7
					for(ll k = 0;k < mode;k++)		//目标数字模7
						for(ll l = 0;l <= 9;l++)
						{
							tmp = (1ll * mode - (l * powr) % mode + k) % mode;
							dp[i][j][k] += dp[i - 1][(j - l%mode + mode) % mode][tmp];
						}
				powr *= 10;
			}
			ll ans = GetAns(b,sum2,lenz2) - GetAns(a-1,sum1,lenz1);
			printf("%lld\n",ans);
		}
	}
    return 0;
}

/*======================
要求计算a和b之间整除mode而且各位和也整除mode的数
按照正常的数位dp,dp[i]统计1ei以下的数的数据
dp[ ][j][k]分别表示各位和模7和数字模7的余数
在这里我从个位开始计算,所以GetAns(x)是对小于等于x的闭区间进行计算的
(也是主要错误点)
再次强调一下数位dp从最高位开始则为闭区间,从各位开始则为开区间
======================*/