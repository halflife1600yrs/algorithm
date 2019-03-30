#include <bits/stdc++.h>

using namespace std;

const int MAXN=5e5+5,DEPTH=20;
int l2g[MAXN];

int get_log(int x)
{ //保存每个数对2的对数
    if(l2g[x]) return l2g[x];
    for(int i=0;i<22;++i)
        if((1<<i)>x) return (l2g[x]=i-1);
}

struct Tree
{
    int top,head[MAXN],father[MAXN][DEPTH],depth[MAXN];
    struct Edge
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    } edges[MAXN<<1];
    void init()
    {
        top=0;
        memset(head,-1,sizeof(head));
    }
    void add(int fr,int to)
    {
        edges[top].set(to,head[fr]);
        head[fr]=top++;
    }
    void bfs(int root)
    { //bfs得到所有结点的第(2^i)个祖先
        queue<int> Q;
        Q.push(root);
        father[root][0]=-1,depth[root]=0;
        int fr,to;
        while(!Q.empty())
        { //标准bfs过程
            fr=Q.front(),Q.pop();
            for(int addr=head[fr];addr!=-1;addr=edges[addr].last)
            {
                to=edges[addr].to;
                if(to==father[fr][0]) continue;
                father[to][0]=fr,depth[to]=depth[fr]+1;
                //关键点，一个数的第(2^i)个祖先是它的第(2^ i-1)个祖先的第(2^ i-1)个祖先
                for(int i=1;(1<<i)<=depth[to];++i)
                    father[to][i]=father[father[to][i-1]][i-1];
                Q.push(to);
            }
        }
    }
    int query(int a,int b)
    {
        if(depth[a]<depth[b]) swap(a,b);
        while(depth[a]>depth[b]) //先抬到同一层
            a=father[a][get_log(depth[a]-depth[b])];
        if(a==b) return a;
        for(int i=get_log(depth[a]);i>=0;--i)
            if(father[a][i]!=father[b][i]) //如果祖先相同，说明高于等于LCA，这时候要continue
                a=father[a][i],b=father[b][i]; //不同的话说明可以继续跳，先跳一步
        return father[a][0];
    }
} T;

int main()
{
    int v,q,root;
    scanf("%d %d %d",&v,&q,&root);
    T.init();
    for(int i=0,fr,to;i<v-1;++i)
    {
        scanf("%d %d",&fr,&to);
        T.add(fr,to);
        T.add(to,fr);
    }
    T.bfs(root);
    for(int i=0,a,b;i<q;++i)
    {
        scanf("%d %d",&a,&b);
        printf("%d\n",T.query(a,b));
    }
    return 0;
}

/*=======================================
added at 2019.Mar25 21:17:18	problem:P3379
最近公共祖先模板题
树上倍增
=======================================*/