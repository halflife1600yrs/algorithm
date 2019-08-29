#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=3e5+5,MAXE=2*MAXV,DEP=20,INF=0x7f7f7f7f;
int V,maxi,mini;
vector<int> query;
bool tag[MAXV];
ll sum;

namespace T
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE];
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to)
    {
        es[top].set(to, head[fr]);
        head[fr] = top++;
    }
    int fa[MAXV][DEP],depth[MAXV],dfn[MAXV],dfs_num;
    void build_lca(int fr)
    {
        dfn[fr]=++dfs_num;
        for(int i=1;(1<<i)<=depth[fr];++i)
            fa[fr][i]=fa[fa[fr][i-1]][i-1];
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa[fr][0]) continue;
            depth[to]=depth[fr]+1;
            fa[to][0]=fr;
            build_lca(to);
        }
    }
    int lca(int a,int b)
    {
        if(depth[a]<depth[b]) swap(a,b);
        for(int i=DEP-1;i>=0;--i)
            if(depth[a]-(1<<i)>=depth[b])
                a=fa[a][i];
        if(a==b) return a;
        for(int i=DEP-1;i>=0;--i)
            if(fa[a][i]!=fa[b][i])
                a=fa[a][i],b=fa[b][i];
        return fa[a][0];
    }
    int S[MAXV];
    void build_fake_tree()
    {
        sort(query.begin(),query.end(),
            [](int a,int b){ return dfn[a]<dfn[b]; });
        int t=top=0,father;
        S[++t]=1,head[1]=-1;
        for(int fr:query)
        {
            if(fr==1) continue;
            if((father=lca(S[t],fr))!=S[t])
            {
                while(dfn[S[t-1]]>dfn[father]) add(S[t-1],S[t]),--t;
                if(father!=S[t-1])
                    head[father]=-1,add(father,S[t]),S[t]=father;
                else
                    add(S[t-1],S[t]),--t;
            }
            head[fr]=-1,S[++t]=fr;
        }
        while(t>1) add(S[t-1],S[t]),--t;
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int q,k,x;
    scanf("%d",&V);
    T::init();
    for(int i=1,fr,to;i<V;++i)
    {
        scanf("%d %d",&fr,&to);
        T::add(fr,to),T::add(to,fr);
    }
    T::build_lca(1);
    scanf("%d",&q);
    for(int i=0;i<q;++i)
    {
        scanf("%d",&k);
        query=vector<int>();
        sum=maxi=0,mini=INF;
        for(int j=0;j<k;++j)
        {
            scanf("%d",&x);
            query.push_back(x),tag[x]=1;
        }
        T::build_fake_tree();
        T::dfs(1);
        printf("%lld %d %d\n",sum,mini,maxi);
        for(int j:query) tag[j]=0;
    }
    return 0;
}