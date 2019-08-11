#pragma GCC optimize ("O2")

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;
const int MAXN=2e5+5,MODE=1e9+7;
int val[MAXN],n,m;
pii bus[MAXN];
vector<int> vec;

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

namespace sgt
{
    int V[MAXN<<3],lazy[MAXN<<3];
    #define lson (pos<<1)
    #define rson (pos<<1|1)
    #define mid ((l+r)>>1)
    void push_down(int len,int pos)
    {
        V[pos]=add(V[pos],len*(ll)lazy[pos]%MODE);
        if(len>1) lazy[lson]=add(lazy[lson],lazy[pos]),lazy[rson]=add(lazy[rson],lazy[pos]);
        lazy[pos]=0;
    }

    int st,en,v;
    void work1(int l,int r,int pos)
    {
        if(st<=l&&r<=en)
        {
            lazy[pos]=add(lazy[pos],v);
            push_down(r-l+1,pos);
            return;
        }
        if(lazy[pos]) push_down(r-l+1,pos);
        if(en<l||r<st) return;
        if(st<=mid) work1(l,mid,lson);
        else if(lazy[lson]) push_down(mid-l+1,lson);
        if(mid+1<=en) work1(mid+1,r,rson);
        else if(lazy[rson]) push_down(r-mid,rson);
        V[pos]=add(V[lson],V[rson]);
    }
    inline void addLR(int _st,int _en,int _v)
    {
        st=_st,en=_en,v=_v;
        work1(0,vec.size()-1,1);
    }

    int p;
    int work2(int l,int r,int pos)
    {
        if(lazy[pos]) push_down(r-l+1,pos);
        if(l==r) return V[pos];
        if(p<=mid) return work2(l,mid,lson);
        else return work2(mid+1,r,rson);
    }
    inline int queryP(int _p)
    {
        p=_p;
        return work2(0,vec.size()-1,1);
    }
}

bool cmp(const pii& a,const pii& b)
{
    return a.second==b.second?a.first>b.first:a.second>b.second;
}

inline int get_pos(int x)
{
    return lower_bound(vec.begin(),vec.end(),x)-vec.begin();
}

int main()
{
    scanf("%d %d",&n,&m);
    if(!m)
    {
        puts("0");
        return 0;
    }
    int l,r;
    vec.reserve(n*2);
    for(int i=0;i<m;++i)
    {
        scanf("%d %d",&l,&r);
        vec.push_back(l);
        vec.push_back(r);
        bus[i].first=l,bus[i].second=r;
    }
    sort(bus,bus+m,cmp);
    if(bus[0].second<n)
    {
        puts("0");
        return 0;
    }
    sort(vec.begin(),vec.end());
    if(vec[0]>0)
    {
        puts("0");
        return 0;
    }
    for(int i=1,j=0;;++i) // 去重
    {
        if(i>=vec.size())
        {
            vec.resize(j+1);
            break;
        }
        if(vec[i]!=vec[j]) vec[++j]=vec[i];
    }
    int mini=bus[m-1].first,posl,posr,v;
    sgt::addLR(vec.size()-1,vec.size()-1,1);
    for(int i=0;i<m;++i)
    {
        l=bus[i].first,r=bus[i].second;
        if(r<mini)
        {
            puts("0");
            return 0;
        }
        posl=get_pos(l),posr=get_pos(r);
        v=sgt::queryP(posr);
        sgt::addLR(posl,posr-1,v);
        if(l<mini) mini=l;
    }
    printf("%d\n",sgt::queryP(0));
    return 0;
}