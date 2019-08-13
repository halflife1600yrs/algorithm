#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5,MAXE=MAXV;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    
}

int main()
{
    
    return 0;
}