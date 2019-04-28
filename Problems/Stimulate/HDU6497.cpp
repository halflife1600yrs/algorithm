#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e3+5;
int l[MAXN],limit[MAXN],a[MAXN];
double v[MAXN];

double calc(int lenz,double v1,double v2,int vm,int a)
{
    double x=(2*vm*vm-v1*v1-v2*v2)/2.0/a;
    if(x>lenz)
    {
        double vx=sqrt((2*a*lenz+v1*v1+v2*v2)/2.0);
        return (2*vx-v1-v2)/a;
    } else
    {
        return (2*vm-v1-v2)/a+(lenz-x)/vm;
    }
}

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%d %d %d",&l[i],&limit[i],&a[i]);
        limit[n]=0x7fffffff;
        v[0]=0;
        for(int i=1;i<=n;++i)
            v[i]=min(1.0*min(limit[i-1],limit[i]),sqrt(v[i-1]*v[i-1]+2*a[i-1]*l[i-1]));
        for(int i=n-1;i>0;--i)
            v[i]=min(v[i],sqrt(v[i+1]*v[i+1]+2*a[i]*l[i]));
        double ans=0;
        for(int i=0;i<n;++i)
            ans+=calc(l[i],v[i],v[i+1],limit[i],a[i]);
        printf("%.6f\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr18 20:16:49	problem:HDU6497
只需要考虑到自行车一直加速减速都不能到达限制的情况就行了
=======================================*/