#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=60,MAXV=MAXN,MAXE=MAXV*MAXV*2;
char str[MAXN][2];
int n;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        es[top].set(to, head[fr]);
        head[fr] = top++;
    }

    bool vis[MAXN];
    int fail;
    bool get;
    void dfs(int st,int l)
    {
        // debug1(st);
        if(l==n)
        {
            // puts("YES");
            get=1;
            return;
        }
        if(fail>n*)
        {
            return;
        }
        vis[st]=1;
        int num=0;
        for(int i=head[st],to;~i;i=es[i].last)
        {
            to=es[i].to;
            ++num;
            if(!vis[to]) dfs(to,l+1);
            if(get) return;
            if(fail>4000) return;
        }
        if(!num)
        {
            ++fail;
        }
        vis[st]=0;
    }

    void work()
    {
        get=0;
        for(int i=0;i<n;++i)
        {
            fail=0;
            memset(vis,0,sizeof(vis));
            dfs(i,1);
            if(get)
            {
                puts("YES");
                return;
            }
        }
        puts("NO");
    }
}

int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
            scanf("%s",str[i]);
        G::init();
        for(int i=0;i<n-1;++i)
        {
            for(int j=i+1;j<n;++j)
            {
                if(str[i][0]==str[j][0]||str[i][1]==str[j][1])
                {
                    G::add(i,j),G::add(j,i);
                }
            }
        }
        G::work();
    }
    return 0;
}