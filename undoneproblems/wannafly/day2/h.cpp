#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1.0);
struct Ball
{
    int x,y,z,r;
}balls[105];

int get_dis2(Ball a,Ball b)
{
    int x=abs(a.x-b.x),y=abs(a.y-b.y),z=abs(a.z-b.z);
    return x*x+y*y+z*z;
}

inline double get_cos(int a,int b2,int c)
{ //注意这里传的dis是平方
    return (a*a+b2-c*c)/(2.0*a*sqrt(1.0*b2));
}

inline double get_v(int r,double h)
{
    return pi*h*h*(r-h/3.0);
}

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%d%d%d%d",&balls[i].x,&balls[i].y,&balls[i].z,&balls[i].r);
        Ball center;
        scanf("%d%d%d%d",&center.x,&center.y,&center.z,&center.r);
        double ans=0.0,_cos,h1,h2;
        int dis,r1,r2;
        for(int i=0;i<n;++i)
        {
            dis=get_dis2(center,balls[i]);
            r1=center.r,r2=balls[i].r;
            if(dis>=(r1+r2)*(r1+r2)) continue;
            if(dis<=abs(r1-r2)*abs(r1-r2))
            {
                ans+=4.0*pi*pow(min(r1,r2),3)/3.0;
                continue;
            }
            _cos=get_cos(r2,dis,r1);
            double tmp=r2*_cos;
            h1=r1-sqrt(1.0*dis)+tmp;
            h2=r2-tmp;
            ans+=get_v(r2,h2)+get_v(r1,h1);
        }
        printf("Case #%d: ",_);
        printf("%.9f\n",ans);
    }
    return 0;
}