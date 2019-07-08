#include <bits/stdc++.h>

using namespace std;

const int MAXN=205,MAXS=2e5+5;

int v,e;
int val[MAXN];

struct Quee
{
    int data[MAXN],t;
    void add(int x) { data[t++]=x; }
    int& operator[](int x) { return data[x]; }
} items;

namespace G
{
// Graph
int top,head[MAXN];
struct Edge
{
    int to,last;
    void set(int _to,int _last) { to=_to,last=_last; }
} edges[MAXN*4];
void init() { top=0,memset(head,-1,sizeof(head)); }
void add(int fr,int to)
{
    edges[top].set(to,head[fr]);
    head[fr]=top++;
}
bool vis[MAXN];
int dfs(int fr,bool choose)
{
    vis[fr]=1;
    int ans;
    if(choose) ans=val[fr];
    else ans=-val[fr];
    int to;
    for(int i=head[fr];~i;i=edges[i].last)
    {
        to=edges[i].to;
        if(!vis[to]) ans+=dfs(to,!choose);
    }
    return ans;
}
void check()
{
    items.t=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=v;++i)
        if(!vis[i]) items.add( abs( dfs(i,1) ) );
}
// Graph
}

bool dp[2][MAXS];

int main()
{
    int T,sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&v,&e);
        sum=0;
        for(int i=1;i<=v;++i)
        {
            scanf("%d",&val[i]);
            val[i]/=100;
            sum+=val[i];
        }
        G::init();
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            G::add(fr,to);
            G::add(to,fr);
        }
        G::check();
        memset(dp,0,sizeof(dp));
        dp[0][items[0]]=1;
        bool pos=1;
        for(int i=1,item;i<items.t;++i)
        {
            item=items[i];
            for(int j=0;j<=sum;++j)
            {
                if(!dp[!pos][j]) continue;
                dp[pos][j+item]=1;
                if(item>j) dp[pos][item-j]=i+1;
                else dp[pos][j-item]=i+1;
                dp[!pos][j]=0;
            }
            pos=!pos;
        }
        int diff=0;
        while(!dp[!pos][diff]) ++diff;
        printf("%d\n",(sum+diff)*50);
    }
    return 0;
}

/*=======================================
added at 2019.May27 21:25:20	problem:2019西安邀请赛dp题
2
4 2
1400 700 2100 900 
1 3
3 4

6 6
100 200 300 400 500 600
1 2
2 3
3 4
4 5
5 6
6 1

1
6 0
100 200 300 400 500 600
并查集合并物品+dp
因为没有看清题目+dp太久没写wa了很久
记住要开滚动数组
=======================================*/