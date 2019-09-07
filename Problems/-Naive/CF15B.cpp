#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int T,n,m,x1,y1,x2,y2;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d %d %d",&n,&m,&y1,&x1,&y2,&x2);
        if(y1>y2) swap(x1,x2),swap(y1,y2);
        if(x1>x2) x1=m-x1+1,x2=m-x2+1;
        int dx1=x1-1,dy1=y1-1,dx2=m-x2,dy2=n-y2;
        x1+=dx2,y1+=dy2,x2-=dx1,y2-=dy1;
        ll ans=n*(ll)m-x1*(ll)y1-(n-y2+1ll)*(m-x2+1ll);
        if(x1>=x2&&y1>=y2) ans+=(x1-x2+1ll)*(y1-y2+1ll);
        printf("%lld\n",ans);
    }
    return 0;
}