#include <bits/stdc++.h>

typedef long long ll;
ll poly[1000];

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        memset(poly,0,sizeof(poly));
        poly[0]=1;
        for(int i=1,a;i<=26;++i)
            if(scanf("%d",&a),a)
                for(int k=999;k>=0;--k)
                    if(poly[k])
                        for(int j=1;j<=a;++j)
                            poly[k+j*i]+=poly[k];
        ll ans=0;
        for(int i=1;i<=50;++i) ans+=poly[i];
        printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-14 12:16:11 HDU2082
生成函数
==================================================================*/