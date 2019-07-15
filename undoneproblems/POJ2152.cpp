#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
const int MAXN=1005;
int w[MAXN],d[MAXN];
int dp[MAXN][MAXN][2]; // dp[i][j][0/1]表示第i个城市,其j级祖先是最近的,这里有/没有的最小花费
int depth[MAXN];
namespace T
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXN<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;++i) scanf("%d",&w[i]);
        for(int i=1;i<=n;++i) scanf("%d",&d[i]);
        for(int i=1,fr,to,l;i<=n;++i)
        {
            scanf("%d%d%d",&fr,&to,&l);
            T::add(fr,to,l);
            T::add(to,fr,l);
        }
        
    }
    return 0;
}