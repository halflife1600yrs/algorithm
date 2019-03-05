#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1);
const double R=1e-10;
struct ball
{
    double x,y,z,r;
    ball():x(0),y(0),z(0),r(0) {}
    double v() { return 4*pi*r*r*r/3; }
};

inline double dis2(double x,double y,double z)
{
    return x*x+y*y+z*z;
}

inline double calcu(ball a,double h) //球缺的高度
{
    return pi*(3*a.r-h)/3*h*h;
}

int main()
{
    ball a,b;
    scanf("%lf%lf%lf%lf",&a.x,&a.y,&a.z,&a.r);
    scanf("%lf%lf%lf%lf",&b.x,&b.y,&b.z,&b.r);
    if(a.r<b.r) swap(a,b);
    double d=dis2(a.x-b.x,a.y-b.y,a.z-b.z);
    if(d<=dis2(a.r-b.r,0,0))
    { //包含
        printf("%.7f\n",a.v());
        return 0;
    } else if(d>=(a.r+b.r)*(a.r+b.r))
    { //不相交
        printf("%.7f\n",a.v()+b.v());
        return 0;
    } else if(d<=a.r*a.r-b.r*b.r)
    {
        double ans=a.v()-calcu(a,a.r-(a.r*a.r+d-b.r*b.r)/(2*sqrt(d)));
        ans+=calcu(b,b.r+(b.r*b.r+d-a.r*a.r)/(2*sqrt(d)));
        printf("%.7f\n",ans);
    } else
    {
        double ans=a.v()-calcu(a,a.r-(a.r*a.r+d-b.r*b.r)/(2*sqrt(d)));
        ans+=b.v()-calcu(b,b.r-(b.r*b.r+d-a.r*a.r)/(2*sqrt(d)));
        printf("%.7f\n",ans);
    }
    return 0;
}