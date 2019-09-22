#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n<4) puts("-1");
        else if(n&1)
        {
            printf("16400");
            for(int i=5;i<n;++i) putchar('0');
            puts("");
        } else
        {
            printf("1144");
            for(int i=4;i<n;++i) putchar('0');
            puts("");
        }
    }
    // for(int i=32;i*i<10000;++i)
    // {
    //     for(int j=1;j<10;++j)
    //     {
    //         int k=i*i/1000;
    //         double x=sqrt((i*i-1000.0*k)/(j*10+k));
    //         double y=sqrt(i*i/j);
    //         if(ceil(x)==floor(x)&&ceil(y)==floor(y))
    //         {
    //             cout<<i<<" "<<j<<" "<<k<<endl;
    //         }
    //     }
    // }
    return 0;
}

/*==================================================================
added at 2019-09-22 22:07:37 NK14736
挺有趣的一道构造体
关键是后面那个for循环暴力寻找长度为奇的答案的解
==================================================================*/