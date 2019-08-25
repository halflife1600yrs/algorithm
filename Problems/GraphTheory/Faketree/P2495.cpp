#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=3e5+5,MAXE=2*MAXV,DEP=19;
const ll INF=0x7f7f7f7f7f7f7f7f;
int V;
vector<int> query;
bool tag[MAXV];

namespace G
{
    int top, head[MAXV];
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l=0) { to = _to, last = _last, l = _l; }
    } edges[MAXE];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to, int l=0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    int fa[MAXV][DEP],depth[MAXV],dfn[MAXV],dfs_num;
    ll cost[MAXV];
    void build_lca(int fr)
    {
        dfn[fr]=++dfs_num;
        for(int i=1;(1<<i)<=depth[fr];++i)
            fa[fr][i]=fa[fa[fr][i-1]][i-1];
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa[fr][0]) continue;
            fa[to][0]=fr;
            depth[to]=depth[fr]+1;
            cost[to]=min(cost[fr],(ll)edges[i].l);
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
            if(fr==1) continue; // 根节点
            if((father=lca(S[t],fr))!=S[t])
            {
                while(dfn[S[t-1]]>dfn[father]) add(S[t-1],S[t]),--t; // 出栈并加边
                if(father!=S[t-1]) head[father]=-1,add(father,S[t]),S[t]=father;
                else add(S[t-1],S[t]),--t;
            }
            head[fr]=-1,S[++t]=fr;
        }
        while(t>1) add(S[t-1],S[t]),--t;
    }
    ll check(int fr)
    {
        if(tag[fr]) return cost[fr];
        ll ans=0,mini=cost[fr];
        for(int i=head[fr];~i;i=edges[i].last)
            ans+=check(edges[i].to);
        return min(ans,mini);
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d",&V);
    int fr,to,l,q;
    G::init();
    for(int i=1;i<V;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G::add(fr,to,l),G::add(to,fr,l);
    }
    G::cost[1]=INF;
    G::build_lca(1);
    scanf("%d",&q);
    for(int i=0,k,a;i<q;++i)
    {
        query=vector<int>();
        scanf("%d",&k);
        for(int j=0;j<k;++j)
        {
            scanf("%d",&a),tag[a]=1;
            query.push_back(a);
        }
        G::build_fake_tree();
        printf("%lld\n",G::check(1));
        for(int i:query) tag[i]=0;
    }
    return 0;
}

/*==================================================================
added at 2019-08-25 09:58:26 P2495
虚树模板题
==================================================================*/