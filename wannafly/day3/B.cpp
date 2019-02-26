#include <bits/stdc++.h>

using namespace std;

const double EXP=5e-4;
typedef pair<int,int> pII;
typedef pair<double,double> pDD;
pII xi,yi,oi;
pDD x,y,o;
int r;

inline double ptop2(pDD p1,pDD p2)
{
    double tmp1=p1.first-p2.first,tmp2=p1.second-p2.second;
    return tmp1*tmp1+tmp2*tmp2;
}

inline double ptol2(int a,int b,int c,pDD p)
{
    int tmp=abs(a*p.first+b*p.second+c);
    return tmp*tmp/(a*a+b*b);
}

int mid(double A)
{
    double C=y.first,B=sqrt(A*A-C*C);
    
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d%d",&xi.first,&xi.second,&yi.first,&yi.second,&oi.first,&oi.second,&r);
        pDD mid((x.first+y.first)/2.0,(x.second+y.second)/2.0);
        double dis=ptop2(mid,oi);
        o.second=sqrt(ptol2(y.second-x.second,x.first-y.first,y.second*x.second-x.first*y.second,oi));
        o.first=sqrt(dis-o.second);
        x.first=-(y.first=sqrt(ptop2(xi,yi)/2));
        x.second=y.second=0;
        double begin=sqrt(dis)/2,end=(sqrt(ptop2(oi,xi))+sqrt(ptop2(oi,yi)))/2;
        while(end-begin<EXP)
        {
            double mid=(begin+end)/2;
            int state=check(mid);
            if(!state) begin=mid;
            else if(state==2) end=mid;
            else
            {
                printf("%d\n",mid);
                break;
            }
        }
    }
    return 0;
}