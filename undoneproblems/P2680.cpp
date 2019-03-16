#include <bits/stdc++.h>

using namespace std;

const int MAXN=3e5+5;
typedef pair<int,int> Pii;
struct Tree
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last,t;
        void set(int _to,int _last,int _t) { to=_to,last=_last,t=_t; }
    } edges[MAXN<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,int t)
    {
        edges[top].set(to,head[fr],t);
        head[fr]=top++;
    }
} T;
Pii path[MAXN];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a,b,t;
    for(int i=0;i<n-1;++i)
    {
        scanf("%d %d %d",&a,&b,&t);
        T.add(a,b,t);
        T.add(b,a,t);
    }
    for(int i=0;i<m;++i) scanf("%d %d",&path[i].first,&path[i].second);
    
    return 0;
}