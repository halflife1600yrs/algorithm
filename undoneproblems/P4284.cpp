#include <bits/stdc++.h>

using namespace std;

const int MAXN=5e5+5;
int val[MAXN];
int n;
namespace T
{
    int top,head[MAXN];
    struct Edge
    {
        int to,last;
        double l;
        void set(int _to,int _last,double _l) { to=_to,last=_last,l=_l; }
    } edges[MAXN<<1];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,double l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
}

int main()
{
    
}