#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=2e4+5,MAXE=MAXV*2;
const int D=20,L=62;

struct lb
{
    ll b[L];

    lb() { memset(b,0,sizeof(b)); }
    bool insert(ll x)
    { // 插入失败返回1
        for(int i = L - 1; i >= 0; --i)
            if((x>>i)&1)
                if(b[i])
                    x ^= b[i];
                else
                { // 成功插入
                    b[i] = x;
                    return 0;
                }
        return 1;
    }
    ll query_max()
    {
        ll ans=0;
        for(int i=L-1;i>=0;--i)
            if(b[i] && !((ans>>i)&1))
                ans^=b[i];
        return ans;
    }
    void merge(lb x)
    {
        for(int i=L-1;i>=0;--i)
            if(x.b[i]) insert(x.b[i]);
    }
    void print()
    {
        for(int i=0;i<L;++i)
            if(b[i]) printf("%d ",b[i]);
        puts("-");
    }
};

void merge(const lb& x,const lb& y,lb& z)
{
    z=x;
    for(int i=L-1;i>=0;--i)
        if(y.b[i]) z.insert(y.b[i]);
}

ll val[MAXV];

int lg2[MAXV];
int get_log(int x)
{ //保存每个数对2的对数
    if(lg2[x]) return lg2[x];
    for(int i = 0; i < 22; ++i)
        if((1 << i) > x) return (lg2[x] = i - 1);
    return 0;
}
namespace T
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

    int depth[MAXV],fa[MAXV][D];
    lb basis[MAXV][D]; // 记录每个节点往上2^i的线性基

    void bfs(int root)
    {
        queue<int> q;
        q.push(root);
        fa[root][0]=-1,depth[root]=0;
        basis[root][0].insert(val[root]);
        int fr,to,tmp;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                if(to==fa[fr][0]) continue;
                fa[to][0]=fr,depth[to]=depth[fr]+1;
                basis[to][0].insert(val[to]);
                for(int j=1;(1<<j)<=depth[to];++j)
                {
                    tmp=fa[to][j-1];
                    fa[to][j]=fa[tmp][j-1];
                    merge(basis[to][j-1],basis[tmp][j-1],basis[to][j]);
                }
                q.push(to);
            }
        }
    }
    ll query(int x,int y)
    {
        lb ans;
        if(depth[x]<depth[y]) swap(x,y);
        int k,fa1,fa2;
        ans.insert(val[x]);
        ans.insert(val[y]);
        while(depth[x]>depth[y])
        {
            k=get_log(depth[x]-depth[y]);
            fa1=fa[x][k];
            ans.merge(basis[x][k]);
            x=fa1;
        }
        ans.insert(val[x]);
        if(x==y) return ans.query_max();
        for(int i=get_log(depth[x]);i>=0;--i)
        {
            fa1=fa[x][i],fa2=fa[y][i];
            if(fa1!=fa2)
            {
                ans.merge(basis[x][i]);
                ans.merge(basis[y][i]);
                x=fa1,y=fa2;
            }
        }
        ans.insert(val[x]);
        ans.insert(val[y]);
        ans.insert(val[fa[x][0]]);
        return ans.query_max();
    }
}

int main()
{
    int n,q;
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;++i)
        scanf("%lld",&val[i]);
    T::init();
    for(int i=1,fr,to;i<n;++i)
    {
        scanf("%d %d",&fr,&to);
        T::add(fr,to);
        T::add(to,fr);
    }
    T::bfs(1);
    for(int i=0,x,y;i<q;++i)
    {
        scanf("%d %d",&x,&y);
        printf("%lld\n",T::query(x,y));
    }
    return 0;
}

/*==================================================================
added at 2019-08-05 21:40:47 P3292
7 6
8 0 3 1 7 9 4
1 2
1 3
2 4
2 5
3 6
3 7

1 3
3 4
3 7
4 7
5 6
2 3

9
11
7
15
15
11
一个地方没写longlong导致多调了20-30分钟
==================================================================*/