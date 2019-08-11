#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;
const int MAXN=1e6+5;
const double EPS=1e-6;

double get_ans(int x,int y)
{
    double a=pow(1.0*x*x*y,1.0/3.0);
    double c=y+a,d=x+1.0*x*y/a;
    c*=c,d*=d;
    return sqrt(c+d);
}

int main()
{
    // test();
    int n;
    while(~scanf("%d",&n))
    {
        double ans=0,tmp;
        for(int i=0,x,y;i<n;++i)
        {
            scanf("%d %d",&x,&y);
            tmp=get_ans(x,y);
            if(tmp>ans) ans=tmp;
        }
        printf("%.3lf\n",ans);
    }
    return 0;
}