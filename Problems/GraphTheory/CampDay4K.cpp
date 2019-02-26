#include <bits/stdc++.h>

using namespace std;
const int MAXV=1e5+5;
typedef long long ll;
template<int SIZE>
struct Quee
{
    ll data[SIZE];
    int top;
    void add(ll _data) { data[top++]=_data; }
    ll& operator[](int x) { return data[x]; }
};
Quee<MAXV> Q;
ll val[MAXV];

bool cmp(ll a,ll b) { return a>b; }

int v;
struct Tree
{
    int top,head[MAXV];
    struct Edge
    {
        int to,last;
        // ll v; //to往下
        void set(int _to,int _last) { to=_to,last=_last; }
    } edges[MAXV<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to)
    {
        edges[top].set(to,head[fr]);
        head[fr]=top++;
    }
    ll dfs(int fr,int root)
    {
        ll maxi=0,tmp;
        int to;
        for(int addr=head[fr];addr!=-1;addr=edges[addr].last)
        {
            to=edges[addr].to;
            if(to==root) continue;
            tmp=dfs(to,fr);
            if(tmp>maxi) maxi=tmp;
        }
        return max(0ll,maxi+val[fr]);
    }
    ll choose(int root,int num)
    {
        Q.top=0;
        for(int addr=head[root];addr!=-1;addr=edges[addr].last)
            Q.add(dfs(edges[addr].to,root));
        sort(Q.data,Q.data+Q.top,cmp);
        ll ans=val[root];
        for(int i=0;i<num&&i<Q.top;++i) ans+=Q[i];
        return ans;
    }
} G;

int main()
{
    scanf("%d",&v);
    for(int i=1,j;i<=v;++i)
    {
        scanf("%d",&j);
        if(j>0) val[i]=1ll<<(j-1);
        else if(j<0) val[i]=-(1ll<<(-j-1));
        else val[i]=0;
    }
    G.init();
    int fr,to;
    for(int i=0;i<v-1;++i)
    {
        scanf("%d %d",&fr,&to);
        G.add(fr,to),G.add(to,fr);
    }
    Quee<100> digit;
    ll ans;
    for(int T,q=scanf("%d",&T);T--;)
    {
        scanf("%d",&q);
        ans=G.choose(q,4);
        if(!ans) putchar('0');
        else
        {
            if(ans<0) putchar('-'),ans*=-1;
            for(digit.top=0;ans;ans>>=1)
                if(ans&1) digit.add(1);
                else digit.add(0);
            for(int i=digit.top-1;i>=0;--i)
                if(digit[i]) putchar('1');
                else putchar('0');
        }
        putchar('\n');
    }
    return 0;
}

/*=======================================
added at 2019.Feb26 21:40:11	problem:CampDay4K
经过一个点的两条路径相当于四条从该点出发的路径
由于数据范围小，dfs搜索即可，否则需要每次保存每条边的dfs值
=======================================*/