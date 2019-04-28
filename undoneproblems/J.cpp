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

const int MAXV=1e6+5,MAXE=1e6+5;
int v,e;

struct Quee
{
    int data[MAXV],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} q;

struct Graph
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE<<1]; // 注意!!!边记得开两倍!!!

    int top, head[MAXV];
    bool vis[MAXV];

    void init() { top = 0, fill(head+1,head+v+1,-1); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
};

struct cmp
{
    bool operator()(const int& a,const int& b) { return a>b; }
};
struct TOPSORT : Graph
{
    int in[MAXV];

    void init()
    {
        top=0;
        fill(in+1,in+v+1,0);
        fill(head+1,head+v+1,-1);
    }

    void add(int fr, int to) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        // debug2(fr,to);
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }

    void topsort()
    {
        q.top=0;
        priority_queue<int,vector<int>,cmp> Q;
        for(int i = 1; i <= v; ++i)
            if(!in[i]) Q.push(i);
        int fr, to;
        while(!Q.empty())
        {
            fr = Q.top(), Q.pop();
            q.add(fr);
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(!(--in[to])) Q.push(to);
            }
        }
    }
} G2;

struct BFS : Graph
{
    bool vis[MAXV];
    void bfs(int root)
    {
        priority_queue<int,vector<int>,cmp> Q;
        Q.push(root);
        vis[root]=1;
        int fr,to,num=0;
        while(!Q.empty())
        {
            fr=Q.top(),Q.pop();
            ++num;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                // debug2(fr,to);
                if(vis[to]) continue;
                G2.add(fr,to);
                vis[to]=1;
                Q.push(to);
            }
        }
    }

    int check()
    {
        fill(vis+1,vis+v+1,0);
        int ans=0,cur;
        for(int i=1;i<=v;++i)
            if(!vis[i]) ++ans,bfs(i);
        return ans;
    }
} G1;

int read()
{
    int ans=0;
    bool get=0;
    char c;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans*=10,ans+=c-'0',get=1;
        else if(get) break;
        else continue;
    }
    // debug1(ans);
    return ans;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T=read();
    while(T--)
    {
        v=read(),e=read();
        G1.init(),G2.init();
        for(int i=0,fr,to;i<e;++i)
        {
            fr=read(),to=read();
            G1.add(fr,to);
            G1.add(to,fr);
        }
        printf("%d\n",G1.check());
        G2.topsort();
        for(int i=0;i<q.top-1;++i) printf("%d ",q[i]);
        printf("%d\n",q[q.top-1]);
    }
    return 0;
}

/*=======================================
added at 2019.Apr27 16:34:12	problem:J
4

10 9
5 1
5 2
5 3
5 4
5 6
8 6
8 7
8 9
8 10

6 4
1 2
2 4
3 5
6 5

3 2
1 3
3 2

7 5
1 5
1 7
5 4
3 6
4 2
=======================================*/