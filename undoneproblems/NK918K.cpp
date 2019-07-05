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
const int MAXV=1e3+5,MAXE=MAXV*3;
int v,m,layer[MAXV];
struct Quee
{
    int data[MAXV],s,t;
    void push(int x) { data[t++]=x; }
    int pop() { return data[s++]; }
} q;
struct Graph
{ // 向前星存边框架,后面的算法继承此类;比赛的时候把struct去掉
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
        ++in[to];
    }

    int in[MAXV];

    int topsort()
    {
        q.s=q.t=0;
        memset(layer,0x7f,sizeof(layer));
        for(int i=1;i<=v;++i)
            if(in[i]==1) q.push(i),layer[i]=0;
        int fr,to,maxi=0;
        while(q.s!=q.t)
        {
            fr=q.pop();
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(layer[to]<layer[fr]) continue; // 已经入过队的
                if((--in[to])==1)
                {
                    maxi=max(maxi,(layer[to]=layer[fr]+1));
                    q.push(to);
                }
            }
        }
        return maxi;
    }
} G;

int main()
{
    scanf("%d %d",&v,&m);
    G.init();
    for(int i=0,fr,to;i<v-1;++i)
    {
        scanf("%d %d",&fr,&to);
        G.add(fr,to);
        G.add(to,fr);
    }
    for(int i=0,fr,to;i<m;++i)
    {
        scanf("%d %d",&fr,&to);
        G.add(fr,to);
    }
    int maxi=G.topsort();
    disp(layer,1,v+1)
    for(int i=1;i<=v;++i)
        printf("%c\n",layer[i]==maxi?'1':'0');
    return 0;
}

/*=======================================
added at 2019.Jun09 11:16:39	problem:NK918K
这题构造一个解是使用拓扑排序，但是考虑每个点不对
对于每一个更先的关系，将以后走的人为根的树上，以先走的人为根的子树设置为不能最后走
使用树剖或者其他方法，再补
=======================================*/