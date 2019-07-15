#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const double pi=acos(-1);

int main()
{
    int T;
    scanf("%d",&T);
    int a,b,r,d;
    while(T--)
    {
        scanf("%d %d %d %d",&a,&b,&r,&d);
        if(d==0)
        {
            printf("%d\n",a);
            continue;
        }
        double rad=d/180.0*pi,l=hypot(r+a,b),theta=atan(1.0*b/(r+a));
        if(rad<theta)
        {
            printf("%.8f\n",l*cos(theta-rad)-r);
        } else
        {
            printf("%.8f\n",l-r);
        }
    }
    return 0;
}