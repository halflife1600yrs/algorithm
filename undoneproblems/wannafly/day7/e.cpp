#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
long long dp[45][45][45][2]={
    {},
    {
        {{0,0},{0,1}},
        {{1,0}}
    },
    {
        {{0,0},{0,1},{0,1}},
        {{1,0},{0,0}},
        {{1,0}}
    },
    {
        {{0,0},{0,1},{0,1},{0,1}},
        {{1,0},{1,1},{0,0}},
        {{1,0},{0,0}},
        {{1,0}}
    }
};
int number[MAXN], tail[MAXN], ans[MAXN];
int n, v;
bool correct[MAXN];
struct cmp
{
    bool operator()(int a,int b) { return number[a]>number[b]; }
};
struct Graph
{
    int top, indgre[MAXN], head[MAXN];
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXN * MAXN];
    void init()
    {
        v=0,top = 0;
        memset(indgre, 0, sizeof(indgre));
        memset(head, -1, sizeof(head)); 
    }
    void addedge(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++, ++indgre[to], v++;
    }
    bool TopSort(int* ans)
    {
        priority_queue<int, vector<int>, cmp> q;
        while(!q.empty()) q.pop();
        int fr, to, num = 0;
        for(int i = 0; i < n; ++i)
            if(!indgre[i]) q.push(i);
        while(!q.empty())
        {
            fr = q.top(), q.pop(), ans[num++] = number[fr];
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(!--indgre[to]) q.push(to);
            }
        }
        return num == v;
    }
} G;

int get_tail(int x)
{
    return tail[x]==x?x:tail[x]=get_tail(tail[x]);
}

int main()
{
    while(~scanf("%d", &n))
    {
        G.init();
        memset(correct,0,sizeof(correct));
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &number[i]);
            tail[i]=i;
            if(number[i]%n==i) correct[i]=1;
            else if(i>0&&!correct[i-1]) G.addedge(i-1,i),tail[i-1]=i;
        }
        if(!correct[0]&&!correct[n-1]) G.addedge(n-1,0),tail[n-1]=get_tail(0);
        for(int i=0;i<n;++i)
        {
            if(!correct[i])
            {
                int j=number[i]%n;
                if(correct[j]&&tail[j]==j)
                    if(!correct[(j+1)%n]) G.addedge(j,(j+1)%n),tail[j]=get_tail((j+1)%n);
                if(get_tail(j)==get_tail(i)&&(get_tail(i)-i+n)%n>(get_tail(i)-j+n)%n)
                    j=(get_tail(j)+1)%n;
                while(get_tail(j)!=get_tail(i))
                {
                    j=get_tail(j);
                    G.addedge(j,i);
                    j=(j+1)%n;
                    if(tail[j]==j)
                        if(!correct[(j+1)%n]) G.addedge(j,(j+1)%n),tail[j]=get_tail((j+1)%n);
                }
            }
        }
        G.TopSort(ans);
        for(int i=0;i<n;++i) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}

/*=======================================
added at 2019年Jan26日 21:45:44	problem:e
10
20 10 11 12 14 4 6 13 18 7
4可以比20先放
20          14 4 6    18  
10
11 13 16 8 14 4 6 17 18 28
=======================================*/