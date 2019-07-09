#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;

const int MAXN=1e5+5;
int arr[MAXN];
double logx[MAXN];

inline double get_log(int x)
{
    if(logx[x]) return logx[x];
    return logx[x]=log2(x);
}

int main()
{
    int T;
    scanf("%d",&T);
    int n,m;
    while(T--)
    {
        memset(arr,0,sizeof(arr));
        scanf("%d %d",&n,&m);
        for(int i=0,a;i<n;++i)
        {
            scanf("%d",&a);
            if(a) ++arr[1],--arr[a+1];
        }
        for(int i=0,a;i<m;++i)
        {
            scanf("%d",&a);
            if(a) --arr[1],++arr[a+1];
        }
        double a1=0,a2=0;
        for(int i=2;i<MAXN;++i)
        {
            arr[i]=arr[i-1]+arr[i];
            if(arr[i]==0) continue;
            if(arr[i]>0)
            {
                a1+=arr[i]*get_log(i);
            } else
            {
                a2-=arr[i]*get_log(i);
            }
        }
        // debug2(a1,a2);
        printf("%s\n",abs(a1-a2)<1e-8?"equal":"unequal");
    }
    return 0;
}

/*==================================================================
added at 2019-07-09 09:42:41 NK923B
这题实质上是双哈希
但是用log做也可,不过要控制精度
==================================================================*/