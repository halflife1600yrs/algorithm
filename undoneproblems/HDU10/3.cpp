#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5;
double p[MAXN];

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double a,b,c,d,maxi=0;
        for(int i=0;i<n;++i)
        {
            scanf("%lf",&p[i]);
            if(p[i]>maxi) maxi=p[i];
        }
        if(maxi>=0.5) printf("%.8lf\n",maxi);
        else
        {
            a=p[0],b=1-p[0];
            for(int i=1;i<n;++i)
            {
                c=b*p[i]+a*(1-p[i]),d=b*(1-p[i]);
                a=c,b=d;
            }
            printf("%.8lf\n",a);
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-21 12:44:18 3
1
4
0.4 0.4 0.4 0.4
1 2
0.4 0.4
==================================================================*/