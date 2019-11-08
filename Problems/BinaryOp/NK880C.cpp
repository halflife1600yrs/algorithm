#include <bits/stdc++.h>

using namespace std;
const int MAXN=1e6+5,INF=0x7f7f7f7f;
int n,m,k,q;
int lin[MAXN],col[MAXN];
int cnum=0,lnum=1;

inline int check()
{
    return min(n+m-cnum-lnum,cnum+lnum);
}

int main()
{
    scanf("%d %d %d %d",&n,&m,&k,&q);
    for(int i=0,x,y;i<k;++i)
    {
        scanf("%d %d",&x,&y);
        ++lin[x],++col[y];
    }
    for(int i=2;i<=n;++i)
        if(lin[i]==lin[1]) ++lnum,lin[i]=1;
        else lin[i]=0;
    for(int i=1;i<=m;++i)
        if(col[i]==n-lnum) ++cnum,col[i]=1;
        else col[i]=0;
    lin[1]=1;
    printf("%d\n",check());
    char clear[5],c;
    int pos;
    for(int i=0;i<q;++i)
    {
        scanf("%3[^0-9]",clear);
        scanf("%1[01] %d",&c,&pos);
        if(c=='0')
        {
            if(lin[pos]) --lnum,lin[pos]=0;
            else ++lnum,lin[pos]=1;
            printf("%d\n",check());
        } else
        {
            if(col[pos]) --cnum,col[pos]=0;
            else ++cnum,col[pos]=1;
            printf("%d\n",check());
        }
    }
    return 0;
}

/*=======================================
added at 2019.May13 20:28:26	problem:NK880C
每次操作反转行列
性质是每行每列最多出现两种情况
=======================================*/