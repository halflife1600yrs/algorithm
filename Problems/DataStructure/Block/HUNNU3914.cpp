#pragma GCC optimize ("O2")
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int MAXN=3e4+7;
int n,q,BLOCK;
int a[MAXN],pos[MAXN];
ll ti[MAXN],per[MAXN],ans[MAXN],temp;

struct problem
{
    int l,r,id;
    bool operator < (const problem& x)const
    {
        return pos[l]==pos[x.l] ? r<x.r : l<x.l;
    }
}pro[MAXN];
//树状数组
inline int lowbit(int x)
{
    return x&(-x);
}
void add(int p)
{
    if(!p) return;
    int time=p;
    for(;p<MAXN;p+=lowbit(p))
        ti[p]+=time,++per[p];
}
void del(int p)
{
    if(!p) return;
    int time=p;
    for(;p<MAXN;p+=lowbit(p))
        ti[p]-=time,--per[p];
}
ll query(int l,int r,ll* arry)
{
    if(!r) return 0;
    ll x1=0;
    while (r>0)
        x1+=arry[r],r-=lowbit(r);
    l--;
    while (l>0)
        x1-=arry[l],l-=lowbit(l);
    return x1;
}
//
inline void modify(int pos,const bool mode)
{
    int lenz=a[pos];
    if(!mode) del(lenz);
    ll sum1=query(1,lenz,ti),sum2=query(lenz+1,MAXN-1,per);
    if(mode) temp+=sum1+lenz+lenz*sum2,add(lenz);
    else temp-=sum1+lenz+lenz*sum2;
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        memset(per,0,sizeof(per));
        memset(ti,0,sizeof(ti));
        scanf("%d %d",&n,&q);
        BLOCK=sqrt(n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]),pos[i]=i/BLOCK;
        for(int i=1;i<=q;i++)
            scanf("%d %d",&pro[i].l,&pro[i].r),pro[i].id=i;
        sort(pro+1,pro+q+1);
        int l=1,r=0;
        temp=0;
        for(int i=1;i<=q;i++)
        {
            while (l<pro[i].l) modify(l++,0); // delete
            while(l>pro[i].l) modify(--l,1); // add
            while (r<pro[i].r) modify(++r,1); // add
            while (r>pro[i].r) modify(r--,0); // delete
            ans[pro[i].id]=temp;
        }
        for(int i=1;i<=q;i++)
            printf("%lld\n",ans[i]);
    }
    return 0;
}

/*==================================================================
added at 2019-08-17 20:04:45 HUNNU3914
莫队+权值线段树+贪心
==================================================================*/