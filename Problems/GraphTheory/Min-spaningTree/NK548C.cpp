#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int MAXV=5e6,MAXE=1e7;
int cost[MAXV];
int v,e,k; //点 联系 已经有的 剩余时间
ll t;
 
int u_set[MAXV];
int tmp[MAXV],head;
int getf(int x)
{
    if(u_set[x]==x) return x;
    head=0;
    while(u_set[x]!=x)
    {
        tmp[head++]=x;
        x=u_set[x];
    }
    for(int i=0;i<head;++i) u_set[tmp[i]]=x;
    return x;
}
 
struct Edge
{
    int fr,to,l;
    void set(int _fr,int _to,int _l) { fr=_fr,to=_to,l=_l; }
};
bool cmp(Edge a,Edge b) { return a.l<b.l; }
struct Graph
{
    int top;
    bool used[MAXV];
    Edge edges[MAXE];
    void init() { top=0; }
    void add(int fr,int to,int l) { edges[top++].set(fr,to,l); }
    ll Kruskal()
    {
        for(int i=1;i<=v;++i) u_set[i]=i;
        sort(edges,edges+top,cmp);
        for(int i=0,fr,to,l;i<top;++i)
        {
            fr=edges[i].fr,to=edges[i].to,l=edges[i].l;
            if(l>cost[fr]||l>cost[to])
            {
                used[i]=1;
                if(l<=cost[to]) cost[to]=l;
                else if(l<=cost[fr]) cost[fr]=l;
            }
        }
        ll ans=0;
        int fr,to,x,y;
        for(int i=0;i<e;++i)
        {
            if(used[i]) continue;
            fr=edges[i].fr,to=edges[i].to;
            x=getf(fr),y=getf(to);
            if(x==y) continue;
            ans+=edges[i].l;
            if(cost[x]<cost[y]) u_set[y]=x;
            else u_set[x]=y; // 始终以时间最小的作为父亲节点
        }
        return ans;
    }
} G;

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
}

template<typename t>
inline t read()
{
    t res = 0;
    char ch;
    do ch = nc(); while (ch < 48 || ch > 57);
    do res = res * 10 + ch - 48, ch = nc(); while (ch >= 48 && ch <= 57);
    return res;
}
 
int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    v=read<int>(),e=read<int>(),k=read<int>(),t=read<ll>();
    G.init();
    for(int i=1;i<=v;++i) cost[i]=read<int>();
    for(int i=0,j;i<k;++i)
    {
        j=read<int>();
        cost[j]=0;
    }
    for(int i=0,fr,to,l;i<e;++i)
    {
        fr=read<int>(),to=read<int>(),l=read<int>();
        G.add(fr,to,l);
    }
    ll ans=G.Kruskal();
    for(int i=1;i<=v;++i)
        if(u_set[i]==i) ans+=cost[i];
    if(ans<=t) printf("Yes\n");
    else printf("No\n");
    return 0;
}
 
/*=======================================
added at 2019.Apr05 21:35:07    problem:NK548C
8 7 0 200
1 2 3 4 5 6 7 8
3 5 4
4 5 2
6 5 1
7 5 2
6 7 9
7 8 8
6 8 3
卡常题，但是最恶心的是数据比题目中给的大，所以最后开大了数组才过
实际上使用fread之后的时间就可以过了
但是这里有几点优化是没有注意的
1、将sort改为计数排序
2、并查集的启发式合并(这里要学一下)
=======================================*/