#include <bits/stdc++.h>

const double eps=1e-6;

inline double pi(double p,int n)
{ // p^i前缀和
    double po=pow(p,n+1);
    return (1-po)/(1-p);
}

inline double pii(double p,int n)
{ // i*p^i前缀和
    double po=pow(p,n+1);
    return (p-po)/(1-p)/(1-p)-n*po/(1-p);
}

double get(double p,double q,int k1,int k2)
{
    double p1=pi(p,k1-2),q1=pi(q,k2-2);
    double down=1-p*q*p1*q1;
    double up=(k1-1)*pow(p,k1-1)+q*(p1+pii(p,k1-2))+q*p1*(
        (k2-1)*pow(q,k2-1)+p*(q1+pii(q,k2-2))
    );
    return up/down;
}

int main()
{
    double p;
    for(int T,k1,k2,_=scanf("%d",&T);T--;++_)
    {
        scanf("%lf %d %d",&p,&k1,&k2);
        printf("Case %d: ",_);
        if(p<eps) printf("%d\n",k1);
        else if(p>1-eps) printf("%d\n",k2);
        else printf("%lf\n",1+(1-p)*get(1-p,p,k1,k2)+p*get(p,1-p,k2,k1));
    }
    return 0;
}

/*==================================================================
added at 2019-07-23 11:30:36	LightOJ1408
佛了,没判断除0的情况
推的太僵硬了,要看看别人的推法
==================================================================*/