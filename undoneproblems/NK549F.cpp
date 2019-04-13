#include <bits/stdc++.h>

using namespace std;

const int MAXV = 6e5+5;
int father[MAXV][20],depth[MAXV];
int top,head[MAXV],l2g[MAXV];
int get_log(int x)
{ //保存每个数对2的对数
    if(l2g[x]) return l2g[x];
    for(int i=0;i<23;++i)
        if((1<<i)>x) return (l2g[x]=i-1);
    return -1;
}
struct Edge
{
    int to,last;
    void set(int _to,int _last) { to=_to,last=_last; }
} edges[MAXV<<1];

void init() { top=0,memset(head,-1,sizeof(head)); }

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
    int ans1=depth[a],ans2=depth[b];
    if(depth[a]<depth[b]) swap(a,b);
    while(depth[a]>depth[b]) //先抬到同一层
        a=father[a][get_log(depth[a]-depth[b])];
    if(a==b)
        return ans1+ans2-2*depth[a];
    for(int i=get_log(depth[a]);i>=0;--i)
        if(father[a][i]!=father[b][i]) //如果祖先相同，说明高于等于LCA，这时候要continue
            a=father[a][i],b=father[b][i]; //不同的话说明可以继续跳，先跳一步
    return ans1+ans2-2*depth[father[a][0]];
}

int main()
{
    int v;
    scanf("%d",&v);
    init();
    int p1,p2;
    for(int i=0,fr,to;i<v-1;++i)
    {
        scanf("%d %d",&fr,&to);
        add(fr,to),add(to,fr);
    }
    bfs(1);
    int q;
    scanf("%d %d",&p1,&p2);
    scanf("%d",&q);
    int ans1,ans2,ans3;
    for(int i=0,fr,to;i<q;++i)
    {
        scanf("%d %d",&fr,&to);
        ans1=query(fr,to);
        ans2=query(fr,p1)+query(to,p2);
        ans3=query(to,p1)+query(fr,p2);
        printf("%d\n",min(ans1,min(ans2,ans3)));
    }
    return 0;
}