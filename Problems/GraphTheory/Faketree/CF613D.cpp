#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=2*MAXV,DEP=18;
int V;
int dp[MAXV];
bool tag[MAXV];
vector<int> query;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, fill(head + 1, head + V + 1, -1); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int fa[MAXV][DEP],depth[MAXV],dfn[MAXV],dfs_num;

    void dfs1(int fr)
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
            dfs1(to);
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
        sort(query.begin(),query.end(),[](int a,int b){ return dfn[a]<dfn[b]; });
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
    int dfs2(int fr)
    { // 返回
        int ans=0,tmp=0;
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            ans+=dfs2(to),tmp+=dp[to];
        }
        if(tag[fr]) dp[fr]=1,ans+=tmp;
        else if(tmp>1) dp[fr]=0,++ans;
        else dp[fr]=tmp;
        return ans;
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d",&V);
    int fr,to,q;
    G::init();
    for(int i=1;i<V;++i)
    {
        scanf("%d %d",&fr,&to);
        G::add(fr,to),G::add(to,fr);
    }
    G::dfs1(1);
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
        bool flag=0;
        for(int i:query)
            if(tag[G::fa[i][0]])
            {
                flag=1;
                puts("-1");
                break;
            }
        if(!flag)
        {
            G::build_fake_tree();
            printf("%d\n",G::dfs2(1));
        }
        for(int i:query) tag[i]=0;
    }
    return 0;
}

/*
4
1 3
2 3
4 3
4
3 1 2 4
*/