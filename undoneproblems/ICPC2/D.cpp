#include <bits/stdc++.h>

using namespace std;

const int MAXV=2e5+5,MAXE=5e5+5;
int V,E;

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    int in[MAXV];
    double dp[MAXV]; // 以拓扑排序求DAG的最长路为例
    void init()
    {
        top = 0;
        fill(head + 1, head + V + 1, -1);
        fill(dp+1,dp+V+1,0);
    }
    void add(int fr, int to) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }
    void toposort()
    {
        queue<int> q;
        fill(dp + 1, dp + V + 1, 0);
        for(int i = 1; i <= V; ++i)
            if(!in[i]) q.push(i),dp[i]=0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(!(--in[to])) q.push(to);
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&V,&E);
        G::init();
        for(int i=0,fr,to;i<E;++i)
        {
            scanf("%d %d",&fr,&to);
            G::add(to,fr);
        }
        G::toposort();
        printf("%.2f\n",G::dp[1]);
    }
    return 0;
}