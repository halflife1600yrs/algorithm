#include <bits/stdc++.h>

using namespace std;

const int MAXV=8e5;

struct Edge
{
    int to,last;
    void set(int _to,int _last) { to=_to,last=_last; }
} es[MAXV<<1];
int top,head[MAXV];
void init() { top=0,memset(head,-1,sizeof(head)); }
void add(int fr,int to)
{
    es[top].set(to,head[fr]);
    head[fr]=top++;
}
int num[3][MAXV],f[MAXV];
void dfs(int fr,int fa)
{
    f[fr]=fa;
    for(int i=head[fr];~i;i=es[i].last)
        if(es[i].to!=fa) dfs(es[i].to,fr);
}

int main()
{
    int v,q;
    scanf("%d %d",&v,&q);
    init();
    for(int i=1,fr,to;i<v;++i)
    {
        scanf("%d %d",&fr,&to);
        add(fr,to),add(to,fr);
    }
    dfs(1,0);
    int a;
    for(int i=0;i<q;++i)
    {
        scanf("%d",&a);
        ++num[0][a],++num[1][f[a]],++num[2][f[f[a]]];
        num[0][0]=0,num[1][0]=num[0][1];
        printf("%d\n",num[0][f[a]]+num[1][f[a]]+num[1][a]+num[2][a]+num[0][f[f[a]]]);
    }
    return 0;
}

/*==================================================================
added at 2019-07-15 11:20:23 NK15158
6 100
1 2
1 3
2 4
2 5
3 6
5 1 3 2 6 4

6 6
1 2
2 3
2 4
2 5
2 6
1 3 4 5 6 2
没有想到用父节点保存子节点的信息
==================================================================*/