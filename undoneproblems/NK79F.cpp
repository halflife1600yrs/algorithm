#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int kind[MAXN];
int n,a,b;
int an,bn,tmpa,tmpb; // 记录查询过程中已经有几个a,几个b,记录暂时的有几个a,几个b,防止同一个子树重复
ll ans=0;
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
    int son_size[MAXN][2]; // son_size[0]包含根的所有子树,son_size[1]所有子树最大
    int mini,heart;
    bool vis[MAXN];
    void getHeart(int fr,int fa)
    {
        int to;
        son_size[fr][0]=1;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa||vis[to]) continue;
            getHeart(to,fr);
            son_size[fr][0]+=son_size[to][0];
            son_size[fr][1]=max(son_size[to][0],son_size[fr][1]);
        }
        // debug1(fr);
        // debug2(son_size[fr][1],son_size[fr][0]);
        int tmp=max(son_size[fr][1],n-son_size[fr][0]);
        // debug1(tmp);
        if(tmp<mini) heart=fr,mini=tmp;
    }
    
    int depth[MAXN]; // 记录dfs过程中每种颜色有几个
    void dfs2(int fr,int fa)
    {
        if(kind[fr]==a)
            ans+=1ll*depth[fr]*bn,++tmpa;
        else if(kind[fr]==b)
            ans+=1ll*depth[fr]*an,++tmpb;
        int to;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa||vis[to]) continue;
            depth[to]=depth[fr]+edges[i].l;
            // debug2(fr,fa);
            debug2(to,kind[to]);
            if(kind[to]==a)
                ans+=1ll*depth[to]*bn,++tmpa;
            else if(kind[to]==b)
                ans+=1ll*depth[to]*an,++tmpb;
        }
    }
    void search(int fr)
    {
        vis[fr]=1;
        debug1(fr);
        depth[fr]=0;
        an=bn=0;
        if(kind[fr]==a) ++an;
        else if(kind[fr]==b) ++bn;
        int to;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            tmpa=tmpb=0;
            depth[to]=edges[i].l;
            dfs2(to,fr);
            an+=tmpa,bn+=tmpb;
            debug2(fr,to);
            debug2(tmpa,tmpb);
        }
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            mini=0x7f7f7ff7;
            getHeart(to,fr);
            debug2(to,heart);
            search(heart);
        }
        vis[fr]=0;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&kind[i]);
    T::init();
    for(int i=1,fr,to,l;i<n;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        T::add(fr,to,l),T::add(to,fr,l);
    }
    int q;
    scanf("%d",&q);
    T::mini=0x7f7f7f7f;
    T::getHeart(1,1);
    int heart=T::heart;
    debug1(heart);
    // debug1(T::heart[1]);
    while(q--)
    {
        scanf("%d %d",&a,&b);
        ans=0;
        T::search(heart);
        printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-10 20:29:51 3
3
1 2 3
1 2 3
2 3 7
3
1 2
==================================================================*/