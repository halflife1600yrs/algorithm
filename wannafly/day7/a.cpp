#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
bool people[MAXN];

struct G
{
    int top,head[MAXN],dis[MAXN];
    struct Node
    {
        int to,last;
        void set(int _to,int _last) { to=_to,last=_last; }
    }nodes[MAXN];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add_edge(int fr,int to)
    {
        nodes[top].set(to,head[fr]),head[fr]=top++;
    }
    void bfs(int start)
    {
        queue<int> q;
        while(!q.empty()) q.pop();
        q.push(start);
        dis[start]=0;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int addr=head[fr];addr!=-1;addr=nodes[addr].last)
            {
                if(dis[to]<=dis[fr]) continue;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int tmp;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&tmp);
        people[i]=tmp==1;
    }

    return 0;
}