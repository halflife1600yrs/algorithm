#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ui;
const int MAXN=2005;
ui id[MAXN];
int u_set[MAXN];

int get_fa(int x)
{
    if(u_set[x]==x) return x;
    return u_set[x]=get_fa(u_set[x]);
}

struct Triad
{
    ui v;
    int i,j;
    Triad() {}
    Triad(ui _v,int _i,int _j):v(_v),i(_i),j(_j) {}
} val[MAXN*MAXN];

bool cmp(const Triad& a,const Triad& b) { return a.v>b.v; }

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        cin>>id[i];
        u_set[i]=i;
    }
    ui sum=0;
    int k=0,maxi,pos;
    for(int i=1;i<n;++i)
    {
        maxi=0,pos=0;
        for(int j=0;j<i;++j)
        {
            val[k++]=Triad(id[i]^id[j],i,j);
        }
    }
    sort(val,val+k,cmp);
    int x,y;
    for(int i=0,limit=n-1;i<k&&limit>0;++i)
    {
        x=get_fa(val[i].i),y=get_fa(val[i].j);
        if(x!=y)
        {
            sum+=val[i].v;
            u_set[x]=y;
            --limit;
        }
    }
    cout<<sum<<endl;
    return 0;
}

/*=======================================
added at 2019.Jun08 21:00:35	problem:NK918G
4
384
320
288
256
其实是最大生成树，刚开始做的时候以为只要简单排序就可以
题目中其实隐含了不能成环的条件
=======================================*/