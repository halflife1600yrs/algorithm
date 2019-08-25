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

const int MAXV=1e3+5,MAXE=2*MAXV;
typedef long long ll;
int V,val[MAXV];
ll sum[MAXV],ans;

namespace T
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head, head + V + 1, -1); }
    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
    void dfs(int fr,int fa)
    {
        sum[fr]=0;
        ll tmp=0x7f7f7f7f7f7f7f7f;
        for(int i=head[fr],to;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(to==fa) continue;
            sum[fr]+=val[to];
            dfs(to,fr);
            tmp=min(tmp,sum[to]);
        }
        if(tmp==0x7f7f7f7f7f7f7f7f) tmp=0;
        ans=max(ans,max((ll)val[fr],tmp)+sum[fr]);
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d",&V);
    T::init();
    for(int i=1,a;i<V;++i)
    {
        scanf("%d",&a);
        T::add(a,i),T::add(i,a);
    }
    for(int i=0;i<V;++i)
        scanf("%d",&val[i]);
    T::dfs(0,-1);
    printf("%lld\n",ans);
    return 0;
}