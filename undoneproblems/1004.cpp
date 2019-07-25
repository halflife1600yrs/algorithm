#include <bits/stdc++.h>

using namespace std;

const int MAXN=5e5+5; // 记得改大

int n,num[MAXN];

bool insert(int val,vector<int> *a)
{
    for (int i=30;i>=0;i--)
        if (val&(1<<i))
        {
            if (!(*a)[i])
            {
                (*a)[i]=val;
                break;
            }
            val^=(*a)[i];
        }
    return val>0;
}

void merge(vector<int> *v1,vector<int> *v2)
{ // 把v1的合并到v2里
    for (int i=0;i<=30;i++)
        if ((*v1)[i])
            insert((*v1)[i],v2);
}

long long query_max(vector<int> *a)
{
    int ans=0;
    for (int i=30;i>=0;i--)
        if ((ans^(*a)[i])>ans)
            ans^=(*a)[i];
    return ans;
}

namespace T
{
    struct Node
    {
        int l,r;
        vector<int> c;
        Node():c(vector<int>(32,0)) {}
    } ns[MAXN<<2];
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    void build(int l,int r,int pos)
    {
        ns[pos].l=l,ns[pos].r=r;
        if(r-l==1)
        {
            if(l<=n) insert(num[l],&(ns[pos].c));
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,lson),build(mid,r,rson);
        merge(&(ns[lson].c),&(ns[pos].c));
        merge(&(ns[rson].c),&(ns[pos].c));
    }
    void query(int fr,int to,int pos,vector<int>* ans)
    {
        int l=ns[pos].l,r=ns[pos].r;
        if(r<=fr||to<=l) return;
        if(fr<=l&&r<=to)
        {
            merge(&(ns[pos].c),ans);
            return;
        }
        query(fr,to,lson,ans);
        query(fr,to,rson,ans);
    }
    void add(int x,int pos)
    {
        int l=ns[pos].l,r=ns[pos].r;
        if(l<=x&&x<=r) insert(x,&(ns[pos].c));
        if(r-l==1) return;
        int mid=(l+r)>>1;
        if(l<=x&&x<mid) add(x,lson);
        else if(mid<=x&&x<r) add(x,rson);
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T,q;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&q);
        for(int i=1;i<=n;++i) scanf("%d",&num[i]);
        T::build(1,n+q+5,1);
        int lastans=0;
        int type,l,r,x;
        for(int i=0;i<q;++i)
        {
            scanf("%d",&type);
            if(type==1)
            {
                scanf("%d",&x);
                T::add(x^lastans,++n);
            } else
            {
                scanf("%d %d",&l,&r);
                l=(l^lastans)%n+1;
                r=(r^lastans)%n+1;
                if(l>r) swap(l,r);
                vector<int> vv(32,0);
                T::query(l,r+1,1,&vv);
                lastans=query_max(&vv);
                printf("%d\n",lastans);
            }
        }
    }
    return 0;
}