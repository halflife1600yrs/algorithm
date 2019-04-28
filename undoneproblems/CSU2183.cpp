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
typedef pair<int,int> pii;
const int MAXN=2e5+5,MAXV=MAXN<<1;
int v,e,u_set[MAXN],top,infor[MAXN];
pii bridge[MAXN];

bool cmp(const pii& a,const pii& b) { return a.first<b.first; }

struct Node
{
    int l,r,v;
    Node *lson,*rson;
    void set(int _l,int _r,int _v=0,Node* _lson=NULL,Node* _rson=NULL) { l=_l,r=_r,v=_v,lson=_lson,rson=_rson; }
    ll lenz() { return 1ll*(r-l+1); }
    bool have(int x)
    {
        if(l<=x&&x<=r) return 1;
        return 0;
    }
} nodes[MAXV];

void init()
{
    top=v+1;
    for(int i=1;i<=v;++i)
    {
        u_set[i]=i;
        nodes[i].set(i,i);
        infor[i]=i;
    }
}

int get_fa(int x)
{
    if(u_set[x]==x) return x;
    return u_set[x]=get_fa(u_set[x]);
}

const int DEPTH = 20; // log_2(MAXV)
int lg2[MAXV];
int get_log(int x)
{ //保存每个数对2的对数
    if(lg2[x]) return lg2[x];
    for(int i = 0; i < 21; ++i)
        if((1 << i) > x) return (lg2[x] = i - 1);
}

int depth[MAXV], fa[MAXV][DEPTH];

void bfs()
{
    depth[top-1]=1;
    for(int i=1;i<20;++i)
        for(int j=1;j<top;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
            if(depth[fa[j][i-1]]) depth[j]=depth[fa[j][i-1]]+(1<<(i-1));
        }
}

int query(int a, int b)
{ // 注意用于处理两点路径信息的时候,都先更新再上跳
    if(depth[a] < depth[b]) swap(a, b);
    while(depth[a] > depth[b]) //先抬到同一层
        a = fa[a][get_log(depth[a] - depth[b])];
    if(a == b) return a;
    for(int i = get_log(depth[a]); i >= 0; --i)
        if(fa[a][i] != fa[b][i]) //如果祖先相同,说明高于等于LCA,这时候要continue
            a = fa[a][i], b = fa[b][i]; //不同的话说明可以继续跳,先跳一步
    // 注意这里还要再更新一次路径信息
    return fa[a][0];
}

ll sum(int start,int end,Node* pos)
{
    ll ans=0;
    if(start<=end)
    {
        if(pos->l>=end) return 0;
        if(pos->r<end) return pos->lenz();
        if(pos->lson->r<end) ans+=pos->lson->lenz()*pos->v;
        else ans+=sum(start,end,pos->lson);
        if(pos->rson->l<end) ans+=sum(start,end,pos->rson);
        return ans;
    } else
    {
        if(pos->r<=end) return 0;
        if(pos->l>end) return pos->lenz();
        if(pos->rson->l>end) ans+=pos->rson->lenz()*pos->v;
        else ans+=sum(start,end,pos->rson);
        if(pos->lson->r>end) ans+=sum(start,end,pos->lson);
        return ans;
    }
}

void connect(int pos,int h)
{
    // debug2(pos,h);
    int x=get_fa(pos),y=get_fa(pos+1);
    // debug2(x,y);
    int m=infor[x],n=infor[y];
    // debug2(m,n);
    // debug1(top);
    nodes[top].set(nodes[m].l,nodes[n].r,h,&nodes[m],&nodes[n]);
    fa[n][0]=top,fa[m][0]=top;
    u_set[x]=y;
    infor[y]=top++;
}

int read()
{
    int ans=0;
    bool get=0;
    char c;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans*=10,ans+=c-'0',get=1;
        else if(get) break;
        else continue;
    }
    return ans;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    v=read();
    for(int i=1;i<v;++i) bridge[i].first=read(),bridge[i].second=i;
    init();
    sort(bridge+1,bridge+v,cmp);
    for(int i=1,pos;i<v;++i)
        connect(bridge[i].second,bridge[i].first);
    bfs();
    // disp(depth,1,top)
    int q,p1,p2;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d %d",&p1,&p2);
        int lca=query(p1,p2);
        // debug1(lca);
        // debug2(nodes[lca].l,nodes[lca].r);
        printf("%lld\n",sum(p1,p2,&nodes[lca]));
    }
    return 0;
}