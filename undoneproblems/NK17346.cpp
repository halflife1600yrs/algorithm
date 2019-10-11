#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5,MAXV=MAXN;
typedef long long ll;
int n,v,e; // n是真实节点的数目
int val[MAXN];
vector<int> ans;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    int in[MAXV];

    void add(int fr, int to) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }

    bool topsort()
    {
        priority_queue<int,vector<int>,greater<int>> q;
        for(int i = 0; i < v; ++i)
            if(!in[i]) q.push(i);
        int fr, to,cnt=0;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            if(0<=fr&&fr<n) // 真实节点作为答案
                ans.push_back(fr),++cnt;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(!(--in[to])) q.push(to);
            }
        }
        if(cnt<n) return 1;
        else return 0;
    }
}


namespace sgt
{
#define lson (pos<<1)
#define rson (pos<<1|1)
#define mid ((l+r)>>1)
    int V[MAXV<<2];
    bool flag[MAXV<<2]; // 记录这个区间有没有-1
    void build(int l,int r,int pos=1)
    {
        V[pos]=v++;
        if(r-l==1)
        { // 底层是真实节点
            G::add(l,V[pos]);
            G::add(r,V[pos]);
            if(val[l]==-1||val[r]==-1) flag[pos]=1;
            else flag[pos]=0;
        } else if(r-l>1)
        {
            build(l,mid,lson),build(mid+1,r,rson);
            G::add(V[lson],V[pos]),G::add(V[rson],V[pos]);
            flag[pos]=flag[lson]||flag[rson];
        }
    }
    int x,st,en;
    bool work1(int l,int r,int pos)
    {
        if(en<l||r<st) return 0;
        if(st<=l&&r<=en)
        {
            G::add(V[pos],x);
            return flag[pos];
        }
        bool ans=0;
        if(st<=mid) ans|=work1(l,mid,lson);
        if(mid+1<=en) ans|=work(mid+1,r,rson);
        return ans;
    }
    inline bool add(int _st,int _en,int _x)
    { // 区间连向点,返回这个区间有没有-1
        st=_st,en=_en,x=_x;
        return work1(0,v-1,1);
    }
#undef lson
#undef rson
#undef mid
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i) scanf("%d",&val[i]);
        v=n;
        sgt::build(0,n-1);
        bool flag=0;
        for(int i=0;i<n;++i)
        {
            if(val[i]%n<i) flag|=sgt::add(val[i]%n,i-1,i);
            else if(val[i]%n>i)
            {
                if(i) flag|=sgt::add(0,i-1);
                flag|=sgt::add(val[i]%n,n-1);
            }
        }
        if(flag)
        {
            puts("-1");
            continue;
        }
        if(G::topsort()) puts("-1");
        else
        {
            for(int i=0;i<ans.size()-1;++i) printf("%d ",ans[i]);
            printf("%d\n",ans[ans.size()-1]);
        }
    }
    return 0;
}