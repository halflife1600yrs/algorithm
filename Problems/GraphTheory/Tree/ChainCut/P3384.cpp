#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=1.5e5+5;
ll val[MAXV];
ll MODE;
struct Tree
{
    int top,head[MAXV];
    int depth[MAXV],father[MAXV],maxSon[MAXV],size[MAXV];
    int cur_order,order[MAXV],pos[MAXV],start[MAXV];
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } edges[MAXV<<1];
    void init(int root) { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to)
    {
        edges[top].set(to,head[fr]);
        head[fr]=top++;
    }
    void divide(int root)
    {
        depth[root]=0,father[root]=-1;
        memset(maxSon,-1,sizeof(maxSon));
        dfs1(root);
        order[root]=0,pos[0]=root;
        cur_order=1;
        start[root]=root;
        dfs2(root);
    }
    void dfs1(int fr)
    {
        size[fr]=1;
        for(int addr=head[fr],to;addr!=-1;addr=edges[addr].last)
        {
            to=edges[addr].to;
            if(to==father[fr]) continue;
            father[to]=fr,depth[to]=depth[fr]+1;
            dfs1(to);
            if(size[to]>size[maxSon[fr]]) maxSon[fr]=to;
            size[fr]+=size[to];
        }
    }
    void dfs2(int fr)
    {
        if(maxSon[fr]==-1) return;
        pos[cur_order]=maxSon[fr];
        order[maxSon[fr]]=cur_order++;
        start[maxSon[fr]]=start[fr];
        dfs2(maxSon[fr]);
        for(int addr=head[fr],to;addr!=-1;addr=edges[addr].last)
        {
            to=edges[addr].to;
            if(to==father[fr]||to==maxSon[fr]) continue;
            pos[cur_order]=to;
            order[to]=cur_order++;
            start[to]=to;
            dfs2(to);
        }
    }
} T;

struct SgTree
{
    struct Node
    {
        int l,r;
        ll val,mark;
    } nodes[MAXV<<2];
    void build(int fr,int to,int pos=1)
    {
        nodes[pos].l=fr,nodes[pos].r=to;
        if(to-fr==1)
        {
            nodes[pos].val=val[T.pos[fr]]%MODE;
            return;
        }
        int mid=(fr+to)>>1;
        build(fr,mid,pos<<1);
        build(mid,to,(pos<<1)+1);
        nodes[pos].val=(nodes[pos<<1].val+nodes[(pos<<1)+1].val)%MODE;
    }
    void markdown(int pos)
    {
        ll mark=nodes[pos].mark%MODE,lenz=nodes[pos].r-nodes[pos].l;
        if(!nodes[pos].mark) return;
        if(lenz>1)
        {
            nodes[pos<<1].mark=(nodes[pos<<1].mark+mark)%MODE;
            nodes[(pos<<1)+1].mark=(nodes[(pos<<1)+1].mark+mark)%MODE;
        }
        nodes[pos].val=(nodes[pos].val+mark*lenz%MODE)%MODE;
        nodes[pos].mark=0;
    }
    ll add(int fr,int to,ll v,int pos=1)
    {
        int l=nodes[pos].l,r=nodes[pos].r;
        if(fr<=l&&r<=to)
        {
            nodes[pos].mark+=v;
            markdown(pos);
            return nodes[pos].val;
        }
        markdown(pos);
        if(to<=l||r<=fr) return nodes[pos].val;
        nodes[pos].val=(add(fr,to,v,pos<<1)+add(fr,to,v,(pos<<1)+1))%MODE;
        return nodes[pos].val;
    }
    ll sum(int fr,int to,int pos=1)
    {
        int l=nodes[pos].l,r=nodes[pos].r;
        markdown(pos);
        if(fr<=l&&r<=to) return nodes[pos].val%MODE;
        if(to<=l||r<=fr) return 0;
        return (sum(fr,to,pos<<1)+sum(fr,to,(pos<<1)+1))%MODE;
    }
} sgt;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int v,q,root;
    scanf("%d%d%d%lld",&v,&q,&root,&MODE);
    for(int i=1;i<=v;++i) scanf("%lld",&val[i]);
    T.init(root);
    for(int i=0,fr,to;i<v-1;++i)
    {
        scanf("%d %d",&fr,&to);
        T.add(fr,to);
        T.add(to,fr);
    }
    T.divide(root);
    sgt.build(0,v);
    for(int i=0,method,x,y,z;i<q;++i)
    {
        ll ans;
        scanf("%d",&method);
        switch (method)
        {
            case 1:
            {
                scanf("%d %d %d",&x,&y,&z);
                while(T.start[x]!=T.start[y])
                {
                    int &a=T.depth[T.start[x]]>T.depth[T.start[y]]?x:y;
                    sgt.add(T.order[T.start[a]],T.order[a]+1,z);
                    a=T.father[T.start[a]];
                }
                if(T.order[x]>T.order[y]) swap(x,y);
                sgt.add(T.order[x],T.order[y]+1,z);
                break;
            }
            case 2:
            {
                scanf("%d %d",&x,&y);
                ans=0;
                while(T.start[x]!=T.start[y])
                {
                    int &a=T.depth[T.start[x]]>T.depth[T.start[y]]?x:y;
                    ans=(ans+sgt.sum(T.order[T.start[a]],T.order[a]+1))%MODE;
                    a=T.father[T.start[a]];
                }
                if(T.order[x]>T.order[y]) swap(x,y);
                ans=(ans+sgt.sum(T.order[x],T.order[y]+1))%MODE;
                printf("%lld\n",ans);
                break;
            }
            case 3:
            {
                scanf("%d %d",&x,&y);
                sgt.add(T.order[x],T.order[x]+T.size[x],y);
                break;
            }
            case 4:
            {
                scanf("%d",&x);
                printf("%lld\n",sgt.sum(T.order[x],T.order[x]+T.size[x]));
                break;
            }
        }
    }
    return 0;
}

/*=======================================
added at 2019.Mar29 20:15:49	problem:P3384
树链剖分模板题
待重构
边没开双倍wa了五个小时
=======================================*/