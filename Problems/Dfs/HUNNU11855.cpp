#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char land[4][4];
int limit[25],ans[4][4];
bool conf[24][24];
int able[24][4]={{1,2,3,4},};

char readc()
{
    char c;
    while(c=getchar())
    {
        if('A'<=c&&c<='Z') return c-'A';
        else if(c==EOF) return EOF;
        else continue;
    }
    return c;
}

inline bool palace(int* a,int* b)
{
    if((a[0]^a[1]^b[0]^b[1])!=4) return 1;
    if((a[2]^a[3]^b[2]^b[3])!=4) return 1;
    return 0;
}

inline void put(int lay,int pos)
{
    for(int i=0;i<4;++i) ans[lay][i]=able[pos][i];
}

inline bool check()
{
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            limit[land[i][j]]-=ans[i][j];
    bool s=0;
    for(int i=0;i<26;++i)
        if(limit[i])
        {
            s=1;
            break;
        }
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            limit[land[i][j]]+=ans[i][j];
    return s;
}

void print()
{
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<3;++j) printf("%d",ans[i][j]);
        printf("%d\n",ans[i][3]);
    }
}

void work()
{
    for(int x=0;x<24;++x)
    {
        put(0,x);
        for(int y=0;y<24;++y)
        {
            if(conf[x][y]||palace(able[x],able[y])) continue;
            put(1,y);
            for(int z=0;z<24;++z)
            {
                if(conf[x][z]||conf[y][z]) continue;
                put(2,z);
                for(int i=0;i<4;++i) // 采用异或使得最后一行不会和前面行冲突
                    ans[3][i]=4^ans[0][i]^ans[1][i]^ans[2][i];
                if(check()) continue; // 同时这里也没有必要验证宫了
                print();
                return;
            }
        }
    }
}

void init()
{
    for(int i=1;i<24;next_permutation(able[i],able[i]+4),++i)
        for(int j=0;j<4;++j)
            able[i][j]=able[i-1][j];
    for(int i=0;i<24;++i)
        for(int j=0;j<24;++j)
            for(int k=0;k<4;++k)
                if(able[i][k]==able[j][k])
                    conf[i][j]=1; 
}

int main()
{
    // freopen(".in", "r", stdin);
    init();
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            land[i][j]=readc();
    char c;
    int kind;
    while(c=readc(),c!=-1)
    {
        scanf("%d",&kind);
        limit[c]=kind;
    }
    work();
    return 0;
}

/*=======================================
added at 2019.Jun16 16:51:04	problem:HUNNU11855
dfs题写炸两个小时
原因竟然是多输出了空格
这题的很多优化思路刚开始都没想出来
实际上用上以后写法会简单很多，而且更快
所以第一遍写的很丑
引起深刻教训
=======================================*/