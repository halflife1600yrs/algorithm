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

int land[5][5],val[20];

void move(int x,int y)
{
    for(int i=x;i<4;++i) swap(land[i][y],land[i+1][y]);
    for(int i=y;i<4;++i) swap(land[4][i],land[4][i+1]);
    // for(int i=1;i<=4;++i)
        // disp(land[i],1,5);
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
            // disp(val,1,17);
        }
        if(ans&1) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}

/*==================================================================
added at 2019-07-31 14:02:50 1007
0 1 2 3
5 6 7 4
9 10 11 8
13 14 15 12
==================================================================*/