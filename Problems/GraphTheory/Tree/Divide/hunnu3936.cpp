#include <bits/stdc++.h>

using namespace std;

const int MAXV=2e4+5,MAXE=2*MAXV;
int V,ans;
namespace T
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to, int l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    int sz[2][MAXV], mini, heart; // sz[0]是包含该点为根的子树大小,sz[1]是该点最大的子树
    bool vis[MAXV]; // vis标记有没有被选为根节点
    int get_heart(int fr, int fa, const int& sum)
    {
        sz[0][fr] = 1, sz[1][fr] = 0;
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(vis[to] || to == fa) continue;
            get_heart(to, fr, int(sum));
            sz[0][fr] += sz[0][to];
            sz[1][fr] = max(sz[1][fr], sz[0][to]);
        }
        if(max(sz[1][fr], sum - sz[0][fr]) < mini)
            mini = max(sz[1][fr], sum - sz[0][fr]), heart = fr;
        return heart;
    }
    int dis[MAXV], s_, t_;
    int judge[2020];
    void get_dis(int fr, int fa, int d)
    { // 这是check的附属操作,只用来暂存节点信息,不进行其他操作
        dis[t_++] = (d%=2019);
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(vis[to] || to == fa) continue;
            get_dis(to, fr, d + edges[i].l);
        }
    }
    void check(int fr)
    { // 检查答案,点分治的核心操作
        s_ = t_ = 0; // 清空dis队列
        judge[0]=1;
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(vis[to]) continue;
            get_dis(to, fr, edges[i].l); // 统计子树信息
            for(int i=s_;i<t_;++i)
                ans+=judge[dis[i]?2019-dis[i]:0];
            while(s_ != t_) ++judge[dis[s_++]]; // 加入子树的信息
        }
        for(int i = 0; i < t_; ++i) --judge[dis[i]]; // 不要用memset清空
    }
    void divide(int fr)
    {
        // debug1(fr);
        vis[fr] = 1;
        check(fr);
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(vis[to] || sz[0][to] <= 1) continue;
            divide(get_heart(to, -1, int(mini = sz[0][to])));
        }
    }
}

int main()
{
    while(~scanf("%d",&V))
    {
        int fr,to,l;
        T::init();
        for(int i=1;i<V;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            T::add(fr,to,l),T::add(to,fr,l);
        }
        ans=0;
        fill(T::vis,T::vis+V+1,0);
        T::divide(T::get_heart(1,-1,int(T::mini=V)));
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-09-18 12:46:34 2019省赛I
这个故事告诉我们慎用int&
==================================================================*/