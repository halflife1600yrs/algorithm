#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=1e5+5;
struct
{
    int top,data[MAXN];
    inline void add(int x) { data[top++]=x; }
    inline int operator[](int pos) { return data[pos]; }
} must[2],spec;

int main()
{
    int n,r,m,k,s; //长度为n，r为必经点，m为特殊点，高度为k，开始点为s
    scanf("%d%d%d%d%d",&n,&r,&m,&k,&s);
    must[0].top=must[1].top=spec.top=0;
    int a,b,maxi=-1,mini=n+1;
    while(r--)
    {
        scanf("%d %d",&a,&b);
        must[b].add(a);
        if(a>maxi) maxi=a;
        if(a<mini) mini=a;
    }
    // must[1]._sort(),must[0]._sort();
    while(m--)
    {
        scanf("%d",&a);
        spec.add(a);
    }
    spec.add(1),spec.add(n);
    // spec._sort();
    if(s<mini&&must[1].top) //对于s在单侧的情况，mini和maxi要看b区的点
    {
        mini=n;
        for(int i=0;i<must[1].top;++i)
            if(must[1][i]<mini) mini=must[1][i];
    } else if(s>maxi&&must[1].top)
    {
        maxi=1;
        for(int i=0;i<must[1].top;++i)
            if(must[1][i]>maxi) maxi=must[1][i];
    }
    int top=spec.top,pos1=top-2,pos2=top-1;
    for(int i=0;i<top;++i)
    { //找到通道范围
        if(spec[i]==mini) pos1=i;
        if(spec[i]<mini&&spec[i]>spec[pos1]) pos1=i;
        if(spec[i]==maxi) pos2=i;
        if(spec[i]>maxi&&spec[i]<spec[pos2]) pos2=i;
    }
    // debug2(spec[pos1],spec[pos2]);
    if(!must[1].top)
    {
        if(s<=mini) printf("%d\n",2*(spec[pos2]-s));
        else if(s>=maxi) printf("%d\n",2*(s-spec[pos1]));
        else printf("%d\n",2*(spec[pos2]-spec[pos1]));
        return 0;
    }
    int ans=2*(spec[pos2]-spec[pos1]+k);
    if(s<spec[pos1]) ans+=2*(spec[pos1]-s);
    else if(s>spec[pos2]) ans+=2*(s-spec[pos2]);
    printf("%d\n",ans);
    return 0;
}

/*=======================================
added at 2019.Jan31 20:30:57	problem:A
许多情况没有考虑到
=======================================*/