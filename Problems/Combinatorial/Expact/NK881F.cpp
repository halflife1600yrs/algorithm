#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int x1,y1,x2,y2,x3,y3;
    while(~scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3))
    {
        ll dx1=x1-x2,dy1=y1-y2,dx2=x2-x3,dy2=y2-y3;
        ll s1=abs(dx1*dy2-dx2*dy1);
        printf("%lld\n",11*s1);
    }
    return 0;
}

/*==================================================================
added at 2019-07-18 21:39:13	NK881F
只能用正三角形推一下,然后大概能推广到其他三角形
用期望的定义去做就好了
估计比赛的时候是做不出
==================================================================*/