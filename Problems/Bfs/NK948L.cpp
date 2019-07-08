#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+1;
int vis[MAXN];
struct Q
{
    int data[MAXN],s,t;
    void push(int x,int d) { data[t++]=x,vis[x]=d; }
    int pop() { return data[s++]; }
} q;

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    if(k<=n) printf("%d\n",n-k);
    else
    {
        q.s=q.t=0;
        q.push(n,0);
        int fr;
        while(q.s!=q.t)
        {
            fr=q.pop();
            if(!vis[fr+1]&&fr+1<MAXN) q.push(fr+1,vis[fr]+1);
            if(fr>0&&!vis[fr-1]) q.push(fr-1,vis[fr]+1);
            if((fr<<1)<MAXN&&!vis[fr<<1]) q.push(fr<<1,vis[fr]+1);
            if(vis[k])
            {
                printf("%d\n",vis[k]);
                return 0;
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-07-06 21:07:39 Problem:NK948L.cpp
简单bfs,只更新没有更新过的点,复杂度O(n)
千万不能把n前面的数先加进队列,因为要保证bfs到的是最短路
==================================================================*/