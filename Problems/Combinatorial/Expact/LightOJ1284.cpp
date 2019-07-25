#include <bits/stdc++.h>

using namespace std;

int x,y,z,n;

inline double in(int a,int b)
{
    return 1.0-((a-1.0)*(a-1.0)+(b-a)*(b-a))/(b*b);
}

int main()
{
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d %d %d %d",&x,&y,&z,&n);
        printf("Case %d: ",_);
        if(n==0)
        {
            printf("0\n");
            continue;
        }
        double ans=0,tmp;
        for(int i=1;i<=x;++i)
            for(int j=1;j<=y;++j)
                for(int k=1;k<=z;++k)
                {
                    tmp=in(i,x)*in(j,y)*in(k,z);
                    ans+=(1-pow(1.0-2.0*tmp,n))/2.0;
                }
        printf("%.8lf\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-21 17:27:49	LightOJ1284
这里概率一直算错了
在[1,3]这个区间里想要覆盖2,[1,3]和[3,1]是两次不同的可行操作,而[2,2]只有一次
在这里面两个都是随机选所以不能事先指定先选的点xyz坐标小一点
==================================================================*/