#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=2e5+10,MAXV=8e5+5,MAXE=4e6+5,INF=0x7f7f7f7f;
int V,E;
int n,val[MAXN];
int ans[MAXN],ans_t;

struct cmp
{
    bool operator()(const pii& a,const pii& b)
    {
        return a.second>b.second;
    }
};

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV], in[MAXV];

    void init()
    {
        top = 0;
        fill(head,head+n+5,-1);
        fill(in,in+n+5,0);
    }

    inline void add(int fr, int to)
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr]);
        head[fr] = top++;
        ++in[to];
    }

    bool toposort()
    {
        priority_queue<pii,vector<pii>,cmp> q;
        int fr, to, cnt=0;
        ans_t=0;
        for(int i = 0; i < n; ++i)
            if(!in[i]) q.push(pii(i,val[i]));//,debug2(i,val[i]);
        while(!q.empty())
        {
            fr = q.top().first, q.pop();
            // debug1(fr);
            ++cnt;
            if(fr<n&&val[fr]>=0)
                ans[ans_t++]=val[fr];
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(!(--in[to])) q.push(pii(to,to<n?val[to]:-1));
            }
        }
        return cnt<=V;
    }
}

namespace sgt
{
    int id[MAXN<<2],mini[MAXN<<2];
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    #define mid ((l+r)>>1)
    void build(int l,int r,int pos=1)
    {
        if(r==l)
        {
            id[pos]=l;
            mini[pos]=val[l];
            return;
        }
        id[pos]=++V;
        G::in[id[pos]]=0,G::head[id[pos]]=-1;
        build(l,mid,lson),build(mid+1,r,rson);
        G::add(id[lson],id[pos]),G::add(id[rson],id[pos]);
        mini[pos]=min(mini[lson],mini[rson]);
    }

    int x,st,en;
    bool work(int l,int r,int pos=1)
    {
        if(st<=l&&r<=en)
        {
            G::add(id[pos],x);
            return mini[pos]==-1;
        }
        if(en<l||r<st) return 0;
        bool ans=0;
        if(st<=mid) ans|=work(l,mid,lson);
        if(mid+1<=en) ans|=work(mid+1,r,rson);
        return ans;
    }
    bool addLR(int X,int ST,int EN)
    {
        if(ST>EN) return 0;
        x=X,st=max(0,ST),en=min(n-1,EN);
        return work(0,n-1);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i) scanf("%d",&val[i]);
        V=n-1;
        G::init();
        sgt::build(0,n-1);
        bool flag=0;
        int pos;
        for(int i=0;i<n;++i)
        {
            pos=val[i]%n;
            if(val[i]<0||pos==i) continue; 
            else if(pos<i)
            {
                if(sgt::addLR(i,pos,i-1))
                {
                    flag=1;
                    break;
                }
            } else if(pos>i)
            {
                if(sgt::addLR(i,0,i-1)||sgt::addLR(i,pos,n-1))
                {
                    flag=1;
                    break;
                }
            }
        }
        if(flag)
        {
            puts("-1");
            continue;
        }
        if(G::toposort()) puts("-1");
        else
        {
            for(int i=0;i<ans_t-1;++i) printf("%d ",ans[i]);
            if(ans_t>0) printf("%d",ans[ans_t-1]);
            puts("");
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-16 21:35:14 NK17346
线段树优化建图
这题卡memset!!!!!
==================================================================*/