#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef pair<int,int> Pii;
template<typename T,int SIZE>
struct Quee
{
    T data[SIZE];
    int top;
    void add(T x) { data[top++]=x; }
    T& operator[](int x) { return data[x]; }
};
Quee<Pii,10005> ans;
Quee<int,105> roots;
struct Graph
{
    bool edge[105][105],odd[105],vis[105];
    int v,degree[105],father[105]; //生成树的父亲节点
    void init(int _v)
    {
        v=_v;
        memset(edge,0,sizeof(edge));
        memset(degree,0,sizeof(degree));
    }
    void add(int fr,int to)
    {
        ++degree[fr],++degree[to];
        edge[fr][to]=edge[to][fr]=1;
    }
    void bfs()
    {
        memset(vis,0,sizeof(vis));
        for(int i=1,fr,to;i<=v;++i)
        {
            if(vis[i]) continue;
            roots.add(i);
            queue<int> q;
            q.push(i),vis[i]=1;
            while(!q.empty())
            {
                fr=q.front(),q.pop();
                debug1(fr);
                for(int to=1;to<=v;++to)
                {
                    if(to==fr||vis[to]) continue;
                    if(edge[fr][to])
                    {
                        debug1(to);
                        q.push(to),vis[to]=1;
                    }
                }
            }
        }
    }
    bool sssss()
    {
        memset(vis,0,sizeof(vis));
        for(int i=1,fr,to;i<=v;++i)
        {
            if(vis[i]) continue;
            roots.add(i);
            queue<int> q,leaf;
            q.push(i),vis[i]=1;
            while(!q.empty())
            {
                fr=q.front(),q.pop();
                debug1(fr);
                degree[fr]=0;
                for(int to=1;to<=v;++to)
                {
                    if(to==fr||vis[to]) continue;
                    if(edge[fr][to])
                    {
                        ++degree[fr];
                        father[to]=fr;
                        debug1(to);
                        q.push(to),vis[to]=1;
                    }
                }
                if(!degree[fr]) leaf.push(fr),printf("leaf %d\n",fr);
            }
            for(int i=1;i<=v;++i) printf("%d ",degree[i]);
            printf("\n");
            int step=0;
            while(!leaf.empty())
            {
                debug1(leaf.front());
                fr=leaf.front(),leaf.pop();
                if(fr==i) break;
                to=father[fr];
                if(odd[fr])
                {
                    odd[fr]=0,odd[to]=!odd[to];
                    ans.add(Pii(fr,to));
                    ++step;
                }
                if(!(--degree[to])) leaf.push(to);
            }
            if(odd[i]) return 0;
        }
        return 1;
    }
} G;

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int v,e;
    scanf("%d%d",&v,&e);
    G.init(v);
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        G.add(fr,to);
    }
    if(G.bfs())
    {
        printf("%d\n",ans.top);
        for(int i=0;i<ans.top;++i)
            printf("%d %d\n",ans[i].first,ans[i].second);
    } else printf("-1\n");
    return 0;
}

/*=======================================
added at 2019.Mar28 19:15:14	problem:CSU2284
4 2
1 2
3 4
===
2
1 4
2 3

6 9
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
===
-1

5 6
1 2
1 3
2 3
3 4
4 5
5 1
===
3 5
5 2
2 4
4 1
=======================================*/