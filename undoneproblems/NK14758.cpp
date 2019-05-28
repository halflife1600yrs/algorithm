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
const int MAXN=25,MAXV=MAXN*MAXN,MAXE=MAXV<<2,MODE=1e9+7;
int n,m;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];
    int top, head[MAXV];
    bool vis[MAXV];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to)
    {
        debug2(fr,to);
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
    ll check()
    {
        memset(vis,0,sizeof(vis));
        queue<int> q;
        ll ans=0;
        q.push(0);
        int fr,to,use=0,link;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            vis[fr]=1; // vis记录是否以及更新过
            ++use;
            link=0;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                debug2(fr,to);
                if(vis[to]) ++link;
                else q.push(to),vis[to]=1;
            }
            if(link)
            {
                debug1(link);
                if(!ans) ans=1;
                else ans=ans*link%MODE;
            }
        }
        debug2(ans,use);
        if(use==n*m+1) return ans;
        else return 0;
    }
}

inline int get_p(int i,int j)
{
    if(i==0||i==n+1) return 0;
    if(j==0||j==m+1) return 0;
    return (i-1)*m+j;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        G::init();
        char c;
        for(int i=1;i<=n;++i)
        {
            for(int j=1,p;j<=m;++j)
            {
                while(c=getchar())
                    if(c=='L'||c=='R'||c=='U'||c=='D'||c=='.') break;
                p=get_p(i,j);
                switch (c)
                {
                    case 'L': G::add(p,get_p(i,j-1)); break;
                    case 'R': G::add(p,get_p(i,j+1)); break;
                    case 'U': G::add(p,get_p(i-1,j)); break;
                    case 'D': G::add(p,get_p(i+1,j)); break;
                    case '.':
                        G::add(p,get_p(i,j-1));
                        G::add(p,get_p(i,j+1));
                        G::add(p,get_p(i-1,j));
                        G::add(p,get_p(i+1,j));
                        break;
                    default: break;
                }
            }
        }
        printf("%lld\n",G::check());
    }
    return 0;
}