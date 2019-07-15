#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=505,INF=0x7f7f7f7f;
const int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
char land[MAXN][MAXN];
int dis[MAXN][MAXN],vis[MAXN][MAXN];
pii st,key,door,en;

const int top=MAXN*MAXN*3;
pii d[top];
int s,t;
void push(pii x) { d[t==top-1 ? t=0,top-1 : t++]=x; }
pii pop() { return d[s==top-1 ? s=0,top-1 : s++]; }

int bfs(pii fr,pii to,int time)
{
    #define nxt(arry) (arry[x+xx[i]][y+yy[i]])
    int sx=fr.first,sy=fr.second,tx=to.first,ty=to.second;
    pii f;
    int x,y;
    char c;
    s=t=0;
    push(fr),vis[fr.first][fr.second]=time,dis[fr.first][fr.second]=0;
    while(s!=t)
    {
        f=pop();
        x=f.first,y=f.second;
        for(int i=0;i<4;++i)
        {
            if(nxt(vis)==time) continue;
            nxt(vis)=time;
            if(nxt(land)=='W') continue;
            nxt(dis)=dis[x][y]+1;
            if(nxt(land)!='D') push(pii(x+xx[i],y+yy[i]));
        }
    }
    if(vis[to.first][to.second]==time) return dis[to.first][to.second];
    else return INF;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i)
    {
        scanf("%s",land[i]);
        for(int j=0;j<m;++j)
            switch (land[i][j])
            {
                case 'S': st=pii(i,j); break;
                case 'E': en=pii(i,j); break;
                case 'D': door=pii(i,j); break;
                case 'K': key=pii(i,j); break;
            }
    }
    int ans1=bfs(st,en,1);
    int ans2=dis[key.first][key.second];
    if(vis[key.first][key.second]!=1||vis[door.first][door.second]!=1) ans2=INF;
    else
    { // 能从开始走到钥匙和门
        int ans3=bfs(key,door,2);
        if(ans3==INF) ans2=INF;
        else
        { // 能从钥匙走到门
            int ans4=bfs(door,en,3);
            if(ans4==INF) ans2=INF;
            else ans2+=ans3+ans4; // 能从门走到出口
        }
    }
    printf("%d\n",min(ans1,ans2)==INF?-1:min(ans1,ans2));
    return 0;
}

/*==================================================================
added at 2019-07-14 18:25:41 NK15136
分步走迷宫,思路很简单分步进行bfs就行了
写的还是有点丑
==================================================================*/