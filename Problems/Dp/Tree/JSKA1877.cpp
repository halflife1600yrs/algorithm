#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=2e5+5,MAXE=2*MAXV,MODE=1e9+7;
int V,R;
bool red[MAXV];
int ans[MAXV][1005];

inline int plu(int a,int b)
{
    return (a+=b)>=MODE?a-MODE:a;
}

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
    int sz[MAXV],tmp[1005];
    void dfs(int fr,int fa)
    {
        sz[fr]=red[fr];
        ans[fr][0]=1;
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa) continue;
            dfs(to,fr);
            fill(tmp,tmp+min(sz[fr]+sz[to],R)+1,0);
            for(int j=0;j<=sz[to];++j)
                for(int k=0;k<=sz[fr]&&j+k<=R;++k)
                    tmp[j+k]=plu(tmp[j+k],ans[to][j]*(ll)ans[fr][k]%MODE);
            sz[fr]+=sz[to];
            for(int j=0;j<=sz[fr]+sz[to]&&j<=R;++j) ans[fr][j]=tmp[j];
        }
        ans[fr][red[fr]]=plu(ans[fr][red[fr]],1); // 不是红的也能选
    }
}

int main()
{
    scanf("%d %d",&V,&R);
    T::init();
    for(int i=2,fa;i<=V;++i)
    {
        scanf("%d",&fa);
        T::add(fa,i),T::add(i,fa);
    }
    for(int i=0,j;i<R;++i)
        scanf("%d",&j),red[j]=1;
    T::dfs(1,-1);
    for(int i=0;i<=R;++i) printf("%d\n",ans[1][i]);
    return 0;
}

/*==================================================================
added at 2019-08-27 14:07:28 JSKA1877
树上背包裸题
==================================================================*/