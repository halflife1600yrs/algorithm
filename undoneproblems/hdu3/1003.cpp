#include <bits/stdc++.h>

using namespace std;

const int MAXV=5e4+5,MAXK=100005,MAXE=MAXV<<1;

int judge[MAXK];

namespace T
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } es[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        es[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    int sz[2][MAXV],mini,heart;
    // sz[0]是包含该点为根的子树大小,sz[1]是该点最大的子树
    bool vis[MAXV];
    // vis标记有没有被选为根节点

    void get_heart(int fr,int fa,int sum)
    { // 求重心比较简单,唯一注意就是每次分治时总点数会变所以传一个sum进来
        sz[0][fr]=1,sz[1][fr]=0;
        int to;
        for(int i=head[fr];~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa||vis[to]) continue;
            // 注意找重心这里不能对vis进行标记因为vis是记录有没有选根节点的
            get_heart(to,fr,sum);
            sz[0][fr]+=sz[0][to];
            sz[1][fr]=max(sz[1][fr],sz[0][to]);
        }
        if(max(sz[1][fr],sum-sz[0][fr])<mini)
            mini=max(sz[1][fr],sum-sz[0][fr]),heart=fr;
    }

    void get_dis(int fr,int fa,int d)
    { // 这是check的附属操作,用来记录子树的状态,不进行其他操作
        int to;
        dis.push(d);
        for(int i=head[fr];~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]||to==fa) continue;
            get_dis(to,fr,d+es[i].l);
        }
    }

    void check(int fr)
    {
        dis.s=dis.t=0;
        judge[0]=1; // 这里注意要更新根节点的dis也就是0,防止下面更新距离多次算
        int to;
        for(int i=head[fr];~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]) continue;
            get_dis(to,fr,es[i].l); // 这里是以fr为根遍历所有以to为根的子树里的节点
            // 距离保存在dis队列里
            for(int i=dis.s;i<dis.t;++i)
                for(int j=0;j<query.t;++j)
                    if(query[j]-dis[i]>=0&&judge[query[j]-dis[i]])
                        ++ans[j];
            // dis队列里面的所有值都要先判断能不能构成解再更新,否则出现同一子树里的路径重复算
            while(dis.s!=dis.t) judge[dis.pop()]=1;
        }
        for(int i=0;i<dis.t;++i) judge[dis[i]]=0; // 撤销操作,这里不可memset
    }

    void divide(int fr)
    { // 一般的模板就是这样,变的主要是check函数
        vis[fr]=1;
        check(fr); // 1.遍历当前节点的子树
        int to;
        for(int i=head[fr];~i;i=es[i].last)
        {
            to=es[i].to;
            if(vis[to]||sz[0][to]<=1) continue;
            get_heart(to,fr,mini=sz[0][to]); // 记得更新mini
            divide(to); // 2.找到每个子树的重心然后分治
        }
    }
}


int main()
{
    
    return 0;
}