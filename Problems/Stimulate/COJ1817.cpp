#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
int land[20][20];
const pii dirs[4]={pii(1,0),pii(0,1),pii(-1,0),pii(0,-1)};
const char out[5]="DRUL";
int curd;

int read()
{
    char c;
    while(c=getchar())
    {
        if(c=='#') return 0;
        if(c=='.') return 1;
        if(c=='S') return 2;
        if(c=='T') return 3;
        continue;
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    int x1,y1,x2,y2;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            land[i][j]=read();
            if(land[i][j]==2) x1=i,y1=j;
            else if(land[i][j]==3) x2=i,y2=j;
        }
    curd=1;
    int x=x1,y=y1;
    while(1)
    {
        if(x==x2&&y==y2) break;
        pii right=dirs[(curd+3)%4];
        if(land[x+right.first][y+right.second]==0)
        { // 右边有墙就输出
            printf("%c",out[(curd+3)%4]);
        } else
        {
            curd=(curd+3)%4;
            x+=right.first,y+=right.second;
            continue;
        }
        pii forward=dirs[curd];
        if(land[x+forward.first][y+forward.second]==0)
        { // 前面有墙就输出
            printf("%c",out[curd]);
        } else
        {
            x+=forward.first,y+=forward.second;
            continue;
        }
        pii left=dirs[(curd+1)%4];
        if(land[x+left.first][y+left.second]==0)
        {
            printf("%c",out[(curd+1)%4]);
        } else
        {
            curd=(curd+1)%4;
            x+=left.first,y+=left.second;
            continue;
        }
        pii backward=dirs[(curd+2)%4];
        curd=(curd+2)%4;
        x+=backward.first,y+=backward.second;
    }
    pii right=dirs[(curd+3)%4];
    if(land[x+right.first][y+right.second]==0)
    { // 最后到了终点还要再输
        printf("%c",out[(curd+3)%4]);
    }
    printf("\n");
    return 0;
}

/*=======================================
added at 2019.Jun01 21:51:39	problem:E

=======================================*/