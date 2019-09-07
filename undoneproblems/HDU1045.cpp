#include <bits/stdc++.h>

using namespace std;

char land[5][5];
int n,maxi,cur;

const int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
bool check(int y,int x)
{
    if(land[y][x]!='.') return 0;
    for(int k=0;k<4;++k)
    {
        for(int j=y+yy[k],i=x+xx[k];j>=0&&i>=0&&j<n&&i<n;j+=yy[k],i+=xx[k])
        {
            if(!land[j][i]) return 0;
            if(land[j][i]=='X') break;
        }
    }
    return 1;
}

void dfs(int pos)
{
    maxi=max(maxi,cur);
    for(int i=pos+1;i<n*n;++i)
    {
        int y=i/n,x=i%n;
        if(land[y][x]=='.'&&check(y,x))
        {
            land[y][x]=0,++cur;
            dfs(i);
            land[y][x]='.',--cur;
        }
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;++i)
            scanf("%s",land[i]);
        maxi=cur=0;
        dfs(-1);
        printf("%d\n",maxi);
    }
    return 0;
}