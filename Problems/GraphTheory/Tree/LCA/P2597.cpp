#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=5e6+5,DEP=17;
int V,ans[MAXV];

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE];

    int top, head[MAXV];

    void init() { top = 0, fill(head,head+V+1,-1); }

    void add(int fr, int to)
    {
        es[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int dis[MAXV],fa[MAXV][DEP];

    void insert(int fr,int to)
    {
        dis[fr]=dis[to]+1;
        for(int i=1;(1<<i)<=dis[fr];++i)
            fa[fr][i]=fa[fa[fr][i-1]][i-1];
        ++ans[to];
    }

    int query(int a,int b)
    {
        if(dis[a]<dis[b]) swap(a,b);
        for(int i=DEP-1;i>=0;--i)
            if(dis[a]-(1<<i)>=dis[b])
                a=fa[a][i];
        if(a==b) return a;
        for(int i=DEP-1;i>=0;--i)
            if(fa[a][i]!=fa[b][i])
                a=fa[a][i],b=fa[b][i];
        return fa[a][0];
    }

    int in[MAXV];

    void toposort()
    {
        queue<int> q;
        for(int i=1;i<=V;++i)
            if(!in[i])
            {
                dis[i]=1;
                add(0,i),q.push(i);
            } else fa[i][0]=-1;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                if(fa[to][0]<0) fa[to][0]=fr;
                else fa[to][0]=query(fa[to][0],fr);
                if(!(--in[to]))
                {
                    q.push(to);
                    insert(to,fa[to][0]);
                }
            }
        }
    }

    void dfs(int fr)
    {
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            dfs(to);
            if(dis[fa[to][0]]==dis[fr]) ans[fr]+=ans[to];
        }
    }
}

int main()
{
    scanf("%d",&V);
    G::init();
    int to;
    for(int i=1;i<=V;++i)
        while(scanf("%d",&to),to) G::add(to,i),++G::in[i];
    G::toposort();
    G::init();
    for(int i=1;i<=V;++i) G::add(G::fa[i][0],i);
    G::dfs(0);
    for(int i=1;i<=V;++i)
        printf("%d\n",ans[i]);
    return 0;
}

/*==================================================================
added at 2019-08-18 16:47:27 P2597
直接在dag上dfs是不行的,必须要建树才行
10
0
1 0
1 0
2 3 0
2 3 0
4 0
5 0
7 0
7 0
8 9 0
注意清0的时候绝对不要以可能出现的值作为初始值
下面这组样例7的fa是树根之后又被更新到了
8
0
0
1 0
1 2 0
2 0
3 0
3 4 5 0
5 0
==================================================================*/