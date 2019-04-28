#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;
const int MAXV=100005,MAXE=500005,INF=0x7f7f7f7f;
int v,e;
int lg2[MAXV];
inline int get_log(int x)
{ //保存每个数对2的对数
    if(lg2[x]) return lg2[x];
    for(int i=0;i<22;++i)
        if((1<<i)>x) return (lg2[x]=i-1);
}

inline int sec(int a,int b,int c,int d)
{
    return max(min(a,b),max(c,d));
}

struct Graph
{
    int top,head[MAXV];
    int depth[MAXV],fa[MAXV][20],first[MAXV][20],second[MAXV][20],roots[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXV<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    void check()
    {
        for(int i=1;i<=v;++i)
            if(!roots[i])
                bfs(i);
    }
    void bfs(int root)
    {
        queue<int> q;
        q.push(root);
        fa[root][0]=-1,depth[root]=0;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            roots[fr]=root;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(to==fa[fr][0]) continue;
                depth[to]=depth[fr]+1;
                fa[to][0]=fr;
                first[to][0]=edges[i].l;
                second[to][0]=edges[i].l;
                for(int i=1;(1<<i)<=depth[to];++i)
                {
                    fa[to][i]=fa[fa[to][i-1]][i-1];
                    first[to][i]=max(first[fa[to][i-1]][i-1],first[to][i-1]);
                    second[to][i]=sec(first[fa[to][i-1]][i-1],first[to][i-1],
                        second[fa[to][i-1]][i-1],second[to][i-1]);
                }
                q.push(to);
            }
        }
    }
    int query(int x,int y,int expact)
    {
        debug1(expact);
        debug2(x,y);
        if(roots[x]!=roots[y]) return -1;
        if(depth[x]<depth[y]) swap(x,y);
        int ans1=0,ans2=0;
        while(depth[x]>depth[y])
        {
            ans1=max(ans1,first[x][get_log(depth[x]-depth[y])]); // 先更新答案一定不要搞错了
            ans2=max(ans2,second[x][get_log(depth[x]-depth[y])]);
            x=fa[x][get_log(depth[x]-depth[y])];
        }
        debug2(ans1,ans2);
        if(x==y) return ans1==expact?ans2:ans1;
        for(int i=get_log(depth[x]);i>=0;--i)
            if(fa[x][i]!=fa[y][i])
            {
                ans1=max(ans1,max(first[x][i],first[y][i])); // 先更新答案一定不要搞错了
                ans2=max(ans2,sec(first[x][i],first[y][i],second[x][i],second[y][i]));
                x=fa[x][i],y=fa[y][i];
            }
        ans1=max(ans1,max(first[x][0],first[y][0]));
        ans2=max(ans2,sec(first[x][0],first[y][0],second[x][0],second[y][0]));
        if(ans1==expact) return ans2;
        return ans1;
    }
} mst;

struct Graph2
{
    int top,u_set[MAXV];
    bool use[MAXE];
    struct Edge
    {
        int fr,to,l;
        void set(int _fr,int _to,int _l) { fr=_fr,to=_to,l=_l; }
        bool operator<(const Edge& x)const { return l<x.l; }
    } edges[MAXE];
    void init() { top=0; }
    void add(int fr,int to,int l) { edges[top++].set(fr,to,l); }
    int getfa(int x)
    {
        if(u_set[x]==x) return x;
        return u_set[x]=getfa(u_set[x]);
    }
    ll Kruskal()
    {
        sort(edges,edges+e);
        for(int i=1;i<=v;++i) u_set[i]=i;
        int fr,to,l,x,y,lenz=0;
        ll ans=0;
        for(int i=0;i<e;++i)
        {
            fr=edges[i].fr,to=edges[i].to;
            x=getfa(fr),y=getfa(to);
            if(x==y) continue;
            l=edges[i].l;
            use[i]=1;
            ++lenz,ans+=l;
            mst.add(fr,to,l),mst.add(to,fr,l);
            u_set[x]=y;
        }
        if(lenz!=v-1) return -1;
        return ans;
    }
} G;

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    memset(lg2,0,sizeof(lg2));
    scanf("%d %d",&v,&e);
    G.init(),mst.init();
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G.add(fr,to,l);
    }
    ll mstl=G.Kruskal();
    debug1(mstl);
    mst.check();
    ll mini=INF,tmp;
    for(int i=0;i<e;++i)
    {
        if(G.use[i]) continue;
        tmp=G.edges[i].l-mst.query(G.edges[i].fr,G.edges[i].to,G.edges[i].l);
        debug1(tmp);
        if(!tmp) continue;
        if(mini>tmp) mini=tmp;
    }
    printf("%lld\n",mini+mstl);
    return 0;
}