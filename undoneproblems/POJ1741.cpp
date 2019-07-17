#include <set>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
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

const int MAXV=1e5+5,MAXE=MAXV<<1;

int ans,query;
struct Que
{
    int data[2*MAXV],t;
    void push(int x) { data[t++]=x; }
    int& operator[](int x) { return data[x]; }
} dis,judge;

namespace T
{
    int top,head[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } es[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int l)
    {
        es[top].set(to,head[fr],l);
        head[fr]=top++;
    }

    int sz[2][MAXV],mini,heart;
    bool vis[MAXV];

    void get_heart(int fr,int fa,int sum)
    {
        sz[0][fr]=1,sz[1][fr]=0;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]||to==fa) continue;
            get_heart(to,fr,sum);
            sz[0][fr]+=sz[0][to];
            sz[1][fr]=max(sz[1][fr],sz[0][to]);
        }
        if(max(sz[1][fr],sum-sz[0][fr])<mini)
            mini=max(sz[1][fr],sum-sz[0][fr]),heart=fr;
    }

    void get_dis(int fr,int fa,int d)
    {
        if(d>query) return;
        dis.push(d);
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]||to==fa) continue;
            get_dis(to,fr,d+es[i].l);
        }
    }

    void check(int fr)
    {
        judge.t=0;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]) continue;
            dis.t=0;
            get_dis(to,fr,es[i].l);
            sort(&dis[0],&dis[dis.t],greater<int>());
            ans+=dis.t; // 加上每个点到树根的路径
                                for(int j=0;j<dis.t;++j) printf("%d ",dis[j]);
                                printf("\n");
                                for(int j=0;j<judge.t;++j) printf("%d ",judge[j]);
                                printf("\n");
            int j=0,k=judge.t-1,l;
            while(j<dis.t&&k>=0) // 检查
            {
                if(dis[j]+judge[k]<=query) --k;
                else ++j,ans+=judge.t-k-1;
            }
            if(k<0) ans+=(dis.t-j)*judge.t;
            debug1(ans);
            j=dis.t-1,k=judge.t-1,l=j+k+1; // 归并
            judge.t=l+1;
            debug2(j,k);
            debug2(l,judge.t);
            while(j>=0&&k>=0)
            {
                // debug2(dis[j],judge[k]);
                if(dis[j]<=judge[k]) judge[l--]=dis[j--];
                else judge[l--]=judge[k--];
            }
            while(j>=0) judge[l--]=dis[j--];
        }
    }

    void solve(int fr)
    {
        vis[fr]=1;
        check(fr);
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]||sz[0][to]<=1) continue;
            get_heart(to,fr,sz[0][to]);
            check(to);
        }
    }
}

int main()
{
    int v;
    while(~scanf("%d %d",&v,&query),v)
    {
        T::init();
        for(int i=1,fr,to,l;i<v;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            T::add(fr,to,l),T::add(to,fr,l);
        }
        ans=0;
        memset(T::vis,0,sizeof(T::vis));
        T::get_heart(1,1,T::mini=v);
        T::solve(T::heart);
        printf("%d\n",ans);
    }
    return 0;
}