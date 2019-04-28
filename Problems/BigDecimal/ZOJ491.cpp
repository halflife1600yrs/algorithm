#include <bits/stdc++.h>

using namespace std;

const int MAXN=1500;
char s[MAXN],top;

struct Bigint
{
	int digits[MAXN];
	Bigint() { memset(digits,0,sizeof(digits)); }
	void init() { memset(digits,0,sizeof(digits)); }
	void operator+=(const Bigint& x)
	{
		for(int i=0;i<MAXN;++i)
		{
			digits[i]+=x.digits[i];
			if(digits[i]>=10) digits[i+1]+=digits[i]/10,digits[i]=digits[i]%10;
		}
	}
	void cut()
	{
		for(int i=MAXN;i>=1;--i)
		{
			if(digits[i]&1) digits[i-1]+=10;
			digits[i]=digits[i]>>1;
		}
		digits[0]=digits[0]>>1;
	}
	bool check()
	{
		for(int i=MAXN;i>=0;--i)
			if(digits[i]) return 1;
		return 0;
	}
	void print()
	{
		bool is0=1;
		int i;
		for(i=MAXN;i>=0;--i)
		{
			if(is0&&digits[i]==0) continue;
			is0=0;
			printf("%d",digits[i]);
		}
		if(is0&&i==-1) printf("0");
		printf("\n");
	}
} num,ans;

int main()
{
	int T,n;
	scanf("%d",&T);
    char clear[10];
	while(T--)
	{
		num.init();
		ans.init();
        scanf("%5[ \n]%1500[0-9]",clear,s);
        for(int i=strlen(s)-1,j=0;i>=0;--i,++j) num.digits[j]=s[i]-'0';
		while(num.check())
		{
			num.cut();
			ans+=num;
		}
		ans.print();
	}
	return 0;
}

/*=======================================
added at 2019.Apr20 15:14:00	problem:ZOJ491
计算1000位大数以内所有数的lowbit之和
只要每次除2然后加上去就行了
=======================================*/