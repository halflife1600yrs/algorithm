#include <bits/stdc++.h>

using namespace std;

const int MODE=998244353;
int land[25];

inline int lowbit(int x)
{
    return x&(-x);
}

int main()
{
    int v,e,k;
    scanf("%d %d %d",&v,&e,&k);
    int fr,to;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        --fr,--to;
        land[fr]|=(1<<to),land[to]|=(1<<fr);
    }
    queue<int> q;
    for(int i=0;i<v;++i) q.push(1<<i);

    while(!q.empty())
    {
        int sta=q.front();
        q.pop();
        for(int i=0;i<v;++i)
        {
            if()
        }
    }
    return 0;
}