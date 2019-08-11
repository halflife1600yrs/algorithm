#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=5e5+5;
int top=0;
struct triad
{
    triad(int _fr=0,int _to=0,int _l=0)
    :fr(_fr),to(_to),l(_l) {}
    int fr,to,l;
    bool operator<(const triad& x) const
    {
        return l<x.l;
    }
} es[MAXE];
int uset[MAXV];

int get_fa(int x)
{
    if(x==uset[x]) return x;
    return uset[x]=get_fa(uset[x]);
}

int main()
{
    int v,e;
    scanf("%d %d",&v,&e);
    int fr,to,l;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        es[top++]=triad(fr,to,l);
    }
    sort(es,es+e);
    int x,y,ans=0;
    for(int i=1;i<=v;++i) uset[i]=i;
    for(int i=0;i<e;++i)
    {
        fr=es[i].fr,to=es[i].to;
        x=get_fa(fr),y=get_fa(to);
        if(x==y) continue;
        ans+=es[i].l;
        uset[x]=y;
    }
    printf("%d\n",ans);
    return 0;
}