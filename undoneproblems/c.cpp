#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
const int MODE=1e9+7;

namespace sgTree
{
    #define ls(x) x<<1
    #define rs(x) x<<1|1
    struct Node
    {
        int v;
        int mark[3];
    } nodes[MAXN>>2];
    inline void build(int fr,int to,int pos=1)
    {
        memset(nodes,0,sizeof(nodes));
    }
    void markdown(int pos)
    {
        nodes[pos].v+=mark[0]+mark[1]*
    }
    void set1(int fr,int to,int pos=1)
    {

    }
}

int main()
{

}