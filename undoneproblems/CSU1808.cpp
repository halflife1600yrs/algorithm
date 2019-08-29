#include <bits/stdc++.h>

using namespace std;

const int MAXV=2e5+5,MAXE=3e5+5;
int V,E;

namespace G
{
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, fill(head + 1, head + V + 1, -1); }

    void add(int fr, int to, ll l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
}

int main()
{
    
    return 0;
}