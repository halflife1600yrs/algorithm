#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;

struct cmp
{
    bool operator()(const pli& a,const pli& b)
    {
        return a.first>b.first;
    }
};

int ans[40330][9],pos[40330];
int tans[40330][9],tpos[40330];
void init(int ans[][9],int* pos,int n,bool mode)
{
    int val[9],top=1;
    for(int i=top=1;i<=n;++i) val[i]=i;
    priority_queue<pli,vector<pli>,cmp> q;
    val[0]=0;
    ll tmp;
    do
    {
        tmp=0;
        for(int i=1;i<=n;++i)
        {
            if(mode==1&&i==1) {}
            else tmp*=10,tmp+=val[i]-val[i-1];
            ans[top][i-1]=val[i];
        }
        q.push(pli(tmp,top++));
    } while(next_permutation(val+1,val+n+1));
    int p=1;
    while(!q.empty())
    {
        pos[p]=q.top().second;
        q.pop();
        ++p;
    }
}

int main()
{
    init(ans,pos,8,0);
    int T,n,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        int p;
        if(n<=8)
        {
            init(tans,tpos,n,1);
            p=tpos[k];
            for(int i=0;i<n-1;++i)
                printf("%d ",tans[p][i]);
            printf("%d\n",tans[p][n-1]);
        } else
        {
            printf("%d ",n);
            for(int i=1;i<n-8;++i) printf("%d ",i);
            p=pos[k];
            for(int i=0;i<7;++i)
                printf("%d ",n-9+ans[pos[p]][i]);
            printf("%d\n",n-9+ans[pos[p]][7]);
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-05 19:17:00 2019HDU多校E
求n的全排列中差分数组的字典序是第k小的排列
因为k很小(1e4)所以暴力跑8位以内的数据,然后前面的按n 1 2 3 ...即可
==================================================================*/