#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=255,MAXV=MAXN*MAXN,MAXE=MAXV*8;
int land[MAXN][MAXN],num[MAXN][MAXN];
int v=1,sz[MAXV],id[MAXV];
map<int,int> m;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int vise[MAXE];
    ll visv[MAXV];

    void unique()
    { // 删重边
        memset(vise,-1,sizeof(vise));
        for(int fr=0,to;fr<top;++fr)
        {
            vise[edges[head[fr]].to]=fr;
            for(int i=head[fr],j=edges[i].last;~j;j=edges[j].last)
            {
                to=edges[j].to;
                if(vise[to]==i) edges[i].last=edges[j].last;
                else vise[to]=fr,i=j;
            }
        }
    }

    int val[MAXV];

    void dfs(int fr,int fa,int ID,ll t)
    {
        visv[fr]=t,val[ID]+=sz[fr]; // 更新
        int to;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vise[i]||id[to]!=id[fa]) continue;
            vise[i]=vise[i^1]=1; // 反边也直接标了
            if(visv[to]!=t) dfs(to,fr,ID,t); // 这边一定要这样,不然环的情况会多加一次
        }
    }

    int work()
    {
        memset(vise,0,sizeof(vise)); // 这里用vise标记边有没有遍历过
        int ans=0,to;
        for(int root=1;root<v;++root)
        {
            for(int i=head[root];~i;i=edges[i].last)
                val[id[edges[i].to]]=sz[root];
            for(int i=head[root];~i;i=edges[i].last)
            {
                if(vise[i]) continue;
                to=edges[i].to;
                visv[root]=root*1000005ll+id[to]; // 哈希的时间戳
                vise[i]=vise[i^1]=1;
                dfs(to,root,id[to],root*1000005ll+id[to]);
                ans=max(ans,val[id[to]]);
            }
        }
        return ans;
    }
}

const int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
void dfs(int x,int y,int p)
{
    num[x][y]=p,++sz[p];
    for(int i=0;i<4;++i)
        if(!num[x+xx[i]][y+yy[i]]&&land[x+xx[i]][y+yy[i]]==land[x][y])
            dfs(x+xx[i],y+yy[i],p);
}

int main()
{
    // freopen(".in","r",stdin);
    int n;
    scanf("%d",&n);
    memset(land,-1,sizeof(land));
    int kind=2;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&land[i][j]); // 离散化id
            if(m[land[i][j]]) land[i][j]=m[land[i][j]];
            else m[land[i][j]]=kind,land[i][j]=kind++;
        }
    for(int i=1;i<=n;++i) // 合并连通块
        for(int j=1;j<=n;++j)
            if(!num[i][j])
                id[num[i][j]=v]=land[i][j],dfs(i,j,v++);
    int ans1=0;
    for(int i=1;i<=v;++i)
        if(sz[i]>ans1) ans1=sz[i];
    printf("%d\n",ans1);
    G::init();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        { // 加边
            if(j!=n&&land[i][j]!=land[i][j+1])
                G::add(num[i][j],num[i][j+1]),G::add(num[i][j+1],num[i][j]);
            if(i!=n&&land[i][j]!=land[i+1][j])
                G::add(num[i][j],num[i+1][j]),G::add(num[i+1][j],num[i][j]);
        }
    G::unique(); // 去重边
    printf("%d\n",G::work());
    return 0;
}

/*==================================================================
added at 2019-07-14 09:57:13 NK993I
1.用时间戳优化的dfs
2.去重边
自己想出来的解法写了好久a了,开心
==================================================================*/