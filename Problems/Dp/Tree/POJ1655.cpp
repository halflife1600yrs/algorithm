#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=2e4+5,INF=0x7f7f7f7f;
int dp[MAXN][2]; // dp[i][1]以改节点为根的子树大小,dp[i][0]该节点的所有子树大小
int v;
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
    pii get_heart(int root)
    {
        memset(dp,0,sizeof(dp));
        struct DFS
        {
            int heart,mini;
            void operator()(int fr,int fa)
            {
                int to;
                dp[fr][0]=1;
                for(int i=head[fr];~i;i=edges[i].last)
                {
                    to=edges[i].to;
                    if(to==fa) continue;
                    (*this)(to,fr);
                    dp[fr][0]+=dp[to][0];
                    dp[fr][1]=max(dp[fr][1],dp[to][0]);
                }
                int tmp=max(dp[fr][1],v-dp[fr][0]);
                if(tmp<mini) mini=tmp,heart=fr;
                else if(tmp==mini) heart=min(heart,fr);
            }
        } dfs;
        dfs.mini=INF,dfs(root,-1);
        return pii(dfs.heart,dfs.mini);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&v);
        T::init();
        for(int i=1,fr,to;i<v;++i)
        {
            scanf("%d %d",&fr,&to);
            T::add(fr,to),T::add(to,fr);
        }
        pii ans=T::get_heart(1);
        printf("%d %d\n",ans.first,ans.second);
    }
    return 0;
}

/*==================================================================
added at 2019-08-15 21:53:20 POJ1655
求树的重心水题
==================================================================*/
/*==================================================================
added at 2019-08-25 10:32:32 POJ1655
改成了很骚的套结构体的写法
==================================================================*/