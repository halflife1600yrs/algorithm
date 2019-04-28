#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ui;
typedef long long ll;
const ui MAXN=5e6+5,INF=0xFFFFFFFF;
struct Level
{
    ui min,max;
    int time;
    Level():min(INF),max(0),time(0) {}
    void init() { min=INF,max=0,time=0; }
    void add(ui x)
    { 
        if(x<min) min=x;
        if(x>max) max=x;
        time++;
    }
} levels[33];
ll _2up[33]; //预处理2的幂

int main()
{
    ui k=1;
    for(int i=0;i<=32;++i) _2up[i]=k<<i;
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<=32;++i) levels[i].init();
        ui l;
        for(int i=0;i<n;++i)
        {
            scanf("%u",&l);
            for(int j=0;j<=32;++j)
            {
                if(l<=_2up[j])
                {
                    levels[j].add(l);
                    break;
                }
            }
        }
        bool ok=0;
        for(int i=0;i<=32;++i)
        {
            if(levels[i].time>2)
            {
                ok=1;
                break;
            }
            if(levels[i].time<2) continue;
            if(i&&levels[i].max-levels[i].min<levels[i-1].max)
            {
                ok=1;
                break;
            }
            if(i<32&&0ll+levels[i].max+levels[i].min>levels[i+1].min)
            {
                ok=1;
                break;
            }
        }
        if(!ok)
        {
            for(int i=32;i>1;--i)
            {
                if(levels[i].min<0ll+levels[i-1].max+levels[i-2].max)
                {
                    ok=1;
                    break;
                }
            }
        }
        if(ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*=======================================
added at 2019.Apr19 22:23:11	problem:A
给定5e6条边,要求判断它们中是否能构成三角形
时间和空间卡的比较紧,不能进行排序同时数组最多只能开o(n)
如果可以排序的话从最大向前取3条循环就可以做了
由于三角形最长边小于剩余两边之和(大概可以看成2倍关系)
这里的话我们需要对边按2的k次幂分类
如果一条边小于等于2^k但是比2^(k-1)大,就分到k组
1.对于每一组,如果数量大于2,那么一定可以
2.对于每一组,最大边加最小边大于k+1组的最小边,一定可以
3.对于每一组,最大边减最小边小于k-1组的最大便,一定可以
4.有k+1组最小边<k组最大边+k-1组最大边,一定可以
=======================================*/