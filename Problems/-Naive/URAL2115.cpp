#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5;
int ori[MAXN],val[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&val[i]),ori[i]=val[i];
    sort(val+1,val+n+1);
    int diff=0,p[4];
    for(int i=1;i<=n;++i)
    {
        if(val[i]!=ori[i])
        {
            p[diff++]=i;
            if(diff>2) break;
        }
    }
    if(diff==0)
    {
        printf("Nothing to do here\n");
        return 0;
    }
    int state=diff,q[4];
    diff=0;
    for(int i=n;i>=1;--i)
    {
        if(val[i]!=ori[n-i+1])
        {
            q[diff++]=n+1-i;
            if(diff>2) break;
        }
    }
    if(diff==0)
    {
        printf("Nothing to do here\n");
        return 0;
    } else if(state<=2)
    {   
        if(p[0]>p[1]) swap(p[0],p[1]);
        printf("Yes\n%d %d\n",p[0],p[1]);
        return 0;
    } else if(diff<=2)
    {
        if(q[0]>q[1]) swap(q[0],q[1]);
        printf("Yes\n%d %d\n",q[0],q[1]);
        return 0;
    } else
    {
        printf("No hope\n");
    }
    return 0;
}

/*==================================================================
added at 2019-08-08 15:17:49	E
==================================================================*/