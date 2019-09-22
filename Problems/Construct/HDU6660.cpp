#include <bits/stdc++.h>

using namespace std;

int n,m;
bool change;

inline void pr(int y,int x)
{
    if(change) swap(x,y);
    printf("%d %d\n",y,x);
}

void jump2(int lin)
{
    pr(lin,2);
    pr(lin+1,1);
    pr(lin+1,3);
    int col=4,pos=0;
    while(col<=m) pr(lin+pos,col),pos^=1,++col;
    pr(lin+pos,m-2);
    pr(lin+pos,m);
    pos^=1;
    pr(lin+pos,m-1);
    col=m-3;
    while(col>0) pr(lin+pos,col),pos^=1,--col;
}

void jump3(int lin)
{
    pr(lin,2);
    pr(lin+1,1);
    pr(lin+1,3);
    int col=4,pos=0;
    while(col<=m) pr(lin+pos,col),pos^=1,++col;
    if(m&1)
    {
        pr(lin+2,m-2);
        pr(lin+1,m-1);
        col=m-3,pos=0;
        while(col>0) pr(lin+1+pos,col),pos^=1,--col;
    } else
    {
        pr(lin+2,m-1);
        pr(lin+1,m);
        col=m-2,pos=0;
        while(col>0) pr(lin+1+pos,col),pos^=1,--col;
    }
    col=1,pos=-1;
    while(col<=m) pr(lin+1+pos,col),pos*=-1,++col;
    if(m&1) pr(lin+2,m);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)    
    {
        change=0;
        scanf("%d %d",&n,&m); // 令m>=n
        if(m<n) swap(n,m),change=1;
        if(n==1)
        {
            if(m==1) printf("YES\n1 1\n");
            else printf("NO\n");
        } else if(n==2&&m==2)
        {
            printf("NO\n");
        } else
        {
            puts("YES");
            switch(n%2)
            {
                case 0:
                {
                    int h=1;
                    while(h<n) jump2(h),h+=2;
                }
                break;
                case 1:
                {
                    int h=1;
                    while(h<n-2) jump2(h),h+=2;
                    jump3(h);
                }
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-14 16:55:06 2019HDU多校8D
构造一个行走序列,细节稍微考虑一下
每三行或者每两行一走
==================================================================*/