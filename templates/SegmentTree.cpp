#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int n;
template<typename T>
struct SgTree
{
    int top, start, end;
    struct Node
    {
        int fr, to;
        T data, mark;
        void init(int _fr, int _to) { fr = _fr, to = _to; } //添加：将mark置空
    } nodes[sz << 2];
    void build(int fr, int to)
    {
        node[pos].init(fr, to);
        if(to - fr == 1)
        {
            //初始化
            return;
        }
        int mid = (fr + to) / 2;
        build(fr, mid), build(mid, fr);
        nodes[pos].data = combine(2 * pos, 2 * pos + 1);
    }
    T choose(int pos = 1)
    {
        markdown(pos);
        int fr = nodes[pos].fr, to = nodes[pos].to;
        if(to < start || end < fr) return lose(pos); //完全未命中
        if(start <= fr && to <= end) return hit(pos); //完全命中
        choose(2 * pos), choose(2 * pos + 1);
        return combine(2 * pos, 2 * pos + 1); //部分命中
    }
    T markdown(int pos)
    {
        //
        return nodes[pos].data;
    }
};

int main()
{
    return 0;
}