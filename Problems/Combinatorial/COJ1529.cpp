#include <bits/stdc++.h>

using namespace std;

int l,r,L,R;

inline double ans(double p) { return (p-l)*((R+L)/2.0-p)/(r-l); }

int main()
{
    scanf("%d %d",&l,&r);
    scanf("%d %d",&L,&R);
    double pos=(R+L)/2.0;
    double p=(l+pos)/2.0;
    if(p<=l) printf("0.0000\n");
    else if(r==l) printf("%.4f\n",pos-l);
    else if(p>r) printf("%.4f\n",ans(r));
    else printf("%.4f\n",ans(p));
    return 0;
}