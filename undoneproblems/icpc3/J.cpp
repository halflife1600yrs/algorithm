#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1e6+5,MAXE=2*MAXV,MODE=1e9+7;
int V;
int _inv[MAXV];

inline int plu(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

int quick_pow(int x,int ind)
{
    int ans=1;
    for(;ind;x=x*(ll)x%MODE,ind>>=1)
        if(ind&1) ans=ans*(ll)x%MODE;
    return ans;
}

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to)
    {
        es[top].set(to, head[fr]);
        head[fr] = top++;
    }
    int dis[MAXV],son[MAXV],maxi; // 总的儿子数量,答案正确的儿子数量
    void bfs(int st)
    {
        queue<int> q;
        q.push(st);
        fill(dis+1,dis+V+1,-1);
        dis[st]=maxi=0;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            maxi=max(maxi,dis[fr]);
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                if(~dis[to]) continue;
                ++son[fr];
                dis[to]=dis[fr]+1;
                q.push(to);
            }
        }
    }
    int dfs(int fr)
    {
        if(!son[fr]) return dis[fr]==maxi?1:0;
        int ok=0;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(dis[to]<dis[fr]) continue;
            ok=plu(ok,dfs(to)*(ll)_inv[son[fr]]%MODE);
        }    
        ok=quick_pow(plu(MODE-ok,1),son[fr]);
        ok=plu(MODE-ok,1);
        return ok;
    }
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

int main()
{
    _inv[0]=_inv[1]=1;
    for(int i=2;i<MAXV;i++)
        _inv[i]=((MODE-MODE/i)*(ll)_inv[MODE%i])%MODE;
    read(V);
    int fr,to;
    G::init();
    for(int i=1;i<V;++i)
    {
        read(fr),read(to);
        G::add(fr,to),G::add(to,fr);
    }
    G::bfs(1);
    printf("%d\n",G::dfs(1));
    return 0;
}