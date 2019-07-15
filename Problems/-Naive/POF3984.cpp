#include <cstdio>
#include <queue>

typedef std::pair<int,int> pii;
int land[6][6],xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
bool vis[6][6];
pii pre[6][6];
std::queue<pii> q;

void dfs(int x,int y)
{
    if(pre[x][y].first&&pre[x][y].second) dfs(pre[x][y].first,pre[x][y].second);
    printf("(%d, %d)\n",x-1,y-1);
}

int main()
{
    for(int i=1;i<=5;++i)
        for(int j=1;j<=5;++j)
            scanf("%d",&land[i][j]),land[i][j]^=1;
    q.push(pii(1,1));
    vis[1][1]=1;
    pii fr;
    int x,y,a,b;
    while(!q.empty())
    {
        fr=q.front(),q.pop();
        x=fr.first,y=fr.second;
        if(x==5&&y==5) break;
        for(int i=0;i<4;++i)
            if(!vis[x+xx[i]][y+yy[i]]&&land[x+xx[i]][y+yy[i]])
                pre[x+xx[i]][y+yy[i]]=fr,vis[x+xx[i]][y+yy[i]]=1,q.push(pii(x+xx[i],y+yy[i]));
    }
    dfs(5,5);
    return 0;
}