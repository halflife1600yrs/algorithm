#include <bits/stdc++.h>

using namespace std;

int land[5][5],val[20];

void move(int x,int y)
{
    for(int i=x;i<4;++i) swap(land[i][y],land[i+1][y]);
    for(int i=y;i<4;++i) swap(land[4][i],land[4][i+1]);
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int i=0;i<T;++i)
    {
        int x,y;
        for(int i=1;i<=4;++i)
            for(int j=1;j<=4;++j)
            {
                scanf("%d",&land[i][j]);
                if(!land[i][j]) land[i][j]=16,x=i,y=j;
            }
        move(x,y);
        for(int i=1;i<=4;++i)
            for(int j=1;j<=4;++j)
                val[i*4+j-4]=land[i][j];
        int ans=0;
        bool flag = true;
        while( flag )
        {
            flag = false;
            for(int i=1;i<=16;++i)
            {
                if(val[i]!=i) swap(val[i],val[val[i]]),++ans,flag = true;
            }
        }
        if(ans&1) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 14:02:50 2019HDU多校第四场G
数字华容道
判断一个状态能不能由初态转移过来
与逆序对类似
结论是0在最后的时候,依次把每个数换到它应该在的位置,如果是奇数次就是不可行的
==================================================================*/