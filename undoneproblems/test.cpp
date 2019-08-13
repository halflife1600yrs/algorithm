#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
const double eps=1e-8;
double sum[maxn];
double dp[maxn];
double a[maxn];
int main(){
    // freopen(".in", "r", stdin);
    // freopen("2.out", "w", stdout);
	int l;
	double ans=0.0; 
	double p,q;//掉落的概率   发现的概率 
while(~scanf("%d%lf%lf",&l,&p,&q)){
	for(int i=1;i<=l;i++){
		a[i]=pow(1.0-q,i)*q*(2.0*i);//走了i长度发现机器人掉落时，往返的时间。 
	}
	sum[l+1]=0;
	for(int i=l;i>=0;i--){
		sum[i]=sum[i+1]+a[l-i];
	}
	double ans=0.0;
	for(int i=0;i<l;i++){
		dp[i]=(1.0-p)+p*(sum[i]+pow(1.0-q,l-i+1)*(2*(l-i)));
		dp[i]=dp[i]/(1-p);
		ans+=dp[i];
	//	cout<<dp[i]<<" "<<endl;
	}
	printf("%.10lf\n",ans);
	//cout<<pow(p,2);
}	
	
	return 0;
} 