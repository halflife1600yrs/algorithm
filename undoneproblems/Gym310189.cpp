#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline int get_time(int fi,int hp)
{
    return ceil((sqrt( (2ll*fi-1)*(2ll*fi-1)+8ll*hp )-2*fi+1)/2.0);
}

int main()
{
    cout<<get_time(1,1000000000)<<endl;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int h1,h2,a1,a2;
        scanf("%d %d %d %d",&h1,&h2,&a1,&a2);
        ll ans1=0;
        int t1=get_time(1,h1);
        ans1+=1ll*t1*(a1+a2);
        int t2=get_time(t1+1,h2);
        ans1+=1ll*t2*a2;
        ll ans2=0;
        int s1=get_time(1,h2);
        ans2+=1ll*s1*(a1+a2);
        int s2=get_time(s1+1,h1);
        ans2+=1ll*s2*a1;
        if(ans1<ans2||(ans1==ans2&&t1+t2<=s1+s2))
        {
            printf("%I64d ",ans1);
            for(int i=1;i<=t1;++i) printf("A");
            for(int i=1;i<=t2;++i) printf("B");
        } else
        {
            printf("%I64d ",ans2);
            for(int i=1;i<=s1;++i) printf("B");
            for(int i=1;i<=s2;++i) printf("A");
        }
        printf("\n");
    }
    return 0;
}