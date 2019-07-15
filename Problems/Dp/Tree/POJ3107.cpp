#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN=5e4+5;
int dp[MAXN][2]; // dp[i][1]以改节点为根的子树大小,dp[i][0]该节点的所有子树大小
bool vis[MAXN];
int n,mini=0x7f7f7f7f;
struct Quee
{
    int data[MAXN],t;
    void add(int x) { data[t++]=x; }
    int& operator[](int x) { return data[x]; }
} q;
namespace T
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } edges[MAXN<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to)
    {
        edges[top].set(to,head[fr]);
        head[fr]=top++;
    }
    void dfs1(int fa)
    {
        int to;
        dp[fa][0]=1;
        vis[fa]=1;
        for(int i=head[fa];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            dfs1(to);
            dp[fa][0]+=dp[to][0];
            dp[fa][1]=max(dp[fa][1],dp[to][0]);
        }
        int tmp=max(dp[fa][1],n-dp[fa][0]);
        if(tmp<mini) q.t=0,q.add(fa),mini=tmp;
        else if(tmp==mini) q.add(fa);
    }
}

int main()
{
    while (~scanf("%d",&n))
    {
        T::init();
        for(int i=1,fr,to;i<n;++i)
        {
            scanf("%d%d",&fr,&to);
            T::add(fr,to);
            T::add(to,fr);
        }
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        q.t=0;
        T::dfs1(1);
        sort(q.data,q.data+q.t);
        for(int i=0;i<q.t-1;++i)
            printf("%d ",q[i]);
        printf("%d\n",q[q.t-1]);
    }
    return 0;
}