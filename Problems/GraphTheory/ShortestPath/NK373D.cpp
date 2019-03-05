#include <bits/stdc++.h>

using namespace std;

const int MAXN=3e5+5;
int dis[1<<20];
queue<int> Q;

int read()
{
    char c;
    int ans=0;
    while(c=getchar())
    {
        if(c==' '||c=='\n'||c==EOF) break;
        ans<<=1;
        if(c=='1') ++ans;
    }
    return ans;
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    getchar();
    for(int i=0;i<(1<<m);++i) dis[i]=m;
    Q=queue<int>();
    for(int i=0,j;i<n;++i)
    {
        j=read();
        dis[j]=0,Q.push(j);
    }
    int fr,to;
    while(!Q.empty())
    {
        fr=Q.front(),Q.pop();
        for(int i=0;i<m;++i)
        {
            to=fr^(1<<i);
            if(dis[to]>dis[fr]+1)
            {
                dis[to]=dis[fr]+1;
                Q.push(to);
            }
        }
    }
    int maxi=0;
    for(int i=0;i<(1<<m);++i)
        if(dis[i]>maxi) maxi=dis[i];
    printf("%d\n",m-maxi);
    return 0;
}

/*=======================================
added at 2019.Mar03 13:25:24	problem:NK373D
将一个数的一位翻转后两者异或为0的位有m-1位
可以看成这两个数距离为1
以此类推只要求一个最短路就行
设d[i]为i这个数到所有已有的数最小的距离
将所有d[i]初始化为(是否存在？0：m)
bfs可以得到所有d[i]，答案为m-min{d[i]}
=======================================*/