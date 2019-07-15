#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=505;
const int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
char land[MAXN][MAXN];
int vis[MAXN][MAXN];
pii st,en;

namespace q
{
    const int top=MAXN*MAXN*3;
    pii data[top];
    int s,t;
    void push(pii x) { data[t==top-1 ? t=0,top-1 : t++]=x; }
    pii pop() { return data[s==top-1 ? s=0,top-1 : s++]; }
}

int main()
{
    int n,m,t=2;
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%s",land[i]+1);
            land[i][1+m]=0;
            for(int j=1;j<=m;++j)
                if(land[i][j]=='S') st=pii(i,j);
                else if(land[i][j]=='E') en=pii(i,j);
        }
        pii fr;
        int x,y;
        bool get=0;
        q::s=q::t=0;
        q::push(st),vis[st.first][st.second]=1;
        while(q::s!=q::t)
        {
            fr=q::pop();
            x=fr.first,y=fr.second;
            // debug2(x,y);
            for(int i=0;i<4;++i)
            {
                if(land[x+xx[i]][y+yy[i]]&&land[x+xx[i]][y+yy[i]]!='#'&&vis[x+xx[i]][y+yy[i]]!=t)
                    q::push(pii(x+xx[i],y+yy[i]));
                vis[x+xx[i]][y+yy[i]]=t;
            }
            if(vis[en.first][en.second]==t)
            {
                get=1;
                break;
            }
        }
        printf("%s\n",get?"Yes":"No");
        ++t;
    }
    return 0;
}

/*==================================================================
added at 2019-07-14 16:57:18 NK14572
简单bfs
写的时候没有注意判断vis导致超时
==================================================================*/