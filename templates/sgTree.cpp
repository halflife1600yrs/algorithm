#include <bits/stdc++.h>

using namespace std;

namespace sgTree
{
const int sz = 1e5;
int data[sz];
struct Edge
{
    int fr, to;
    int data, mark;
    int set(int _fr, int _to, int _data) { return fr = _fr, to = _to, data = _data; }
} edges[sz << 2];
int build(int fr = 0, int to = sz, int pos = 1)
{
    if(to - fr == 1) edges[pos].set(fr, to, data[fr]);
    int mid = (fr + to) / 2;
    return edges[pos].set(fr, to, build(fr, mid, 2 * pos) + build(mid, to, 2 * pos + 1));
}
template<typename Op>
struct Selector
{
    int sta, end;
    Op oprt;
    int operator()(int _sta, int _end)
    {
        sta = _sta, end = _end;
        return select();
    }
    int select(int pos = 1)
    {
        int fr = edges[pos].fr, to = edges[pos].to;
        if(fr <= sta && end <= to) return oprt(pos); //完全命中
        if(to <= sta || end <= fr) return oprt(pos); //完全未命中
        return oprt(select(2 * pos), select(2 * pos + 1));
    }
};
struct query
{
    inline int operator()(int a, int b)
    {
        return a + b;
    }
    inline int operator()(int a)
    {
        return a;
    }
};
Selector<query> Query;
}

int main()
{
    sgTree::build();
    sgTree::Query(0, 5);
    return 0;
}