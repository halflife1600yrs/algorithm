#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXV=26,MAXE=300;

int top,u_set[MAXV];

int getf(int x)
{
    if(u_set[x]==x) return x;
    return u_set[x]=getf(u_set[x]);
}

struct triad
{
    int fr,to,v;
    void set(int _fr,int _to,int _v) { fr=_fr,to=_to,v=_v; }
    bool operator<(const triad& x)const { return v<x.v; }
} edges[MAXE];

void init() { top=0; }

void add(int fr,int to,int l) { edges[top++].set(fr,to,l); }

int Kruskal(int v)
{
    for(int i=0;i<v;++i) u_set[i]=i;
    sort(edges,edges+top);
    int ans=0,fr,to,x,y;
    for(int i=0;i<top;++i)
    {
        fr=edges[i].fr,to=edges[i].to;
        x=getf(fr),y=getf(to);
        if(x==y) continue;
        ans+=edges[i].v;
        u_set[y]=x;
    }
    return ans;
}

int readc()
{
    char c;
    while(c=getchar())
    {
        if('A'<=c&&c<='Z') return c-'A';
        else continue;
    }
}

int readi()
{
    char c;
    int ans=0;
    bool get=0;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans=10*ans+c-'0',get=1;
        else if(get) break;
        else continue;
    }
    return ans;
}

int main()
{
    int v;
    while(v=readi())
    {
        init();
        for(int i=0,fr;i<v-1;++i)
        {
            fr=readc();
            for(int j=readi(),to,l;j>0;--j)
            {
                to=readc(),l=readi();
                add(fr,to,l);
            }
        }
        printf("%d\n",Kruskal(v));
    }
    return 0;
}

/*=======================================
added at 2019.Apr16 23:45:35	problem:POJ1251
最小生成树模板题
=======================================*/