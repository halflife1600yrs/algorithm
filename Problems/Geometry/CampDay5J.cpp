#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pII;
typedef pair<double,double> pDD;
const int MAXN=1005;
const int MAXM=2005;
pII edge[MAXM];
pII point[MAXN];
struct Triad
{ //ax+by=c形式的直线
    ll a,b,c;
    Triad():a(0),b(0),c(0) {}
    Triad(ll _a,ll _b,ll _c):a(_a),b(_b),c(_c) {}
    Triad(pII fr,pII to)
    { //给定两个点确定直线的一般式
        a=to.second-fr.second; //y2-y1
        b=fr.first-to.first; //x1-x2
        c=1ll*fr.first*to.second-1ll*to.first*fr.second; //x1y2-x2y1
    }
    ll operator()(pII p) { return a*p.first+b*p.second-c; } //ax+by-c的值
    void show() { printf("%lld %lld %lld\n",a,b,c); }
};

inline int sign(ll x) { return x==0?0:(x>0?1:-1); }

inline int stand(Triad line,pII fr,pII to)
{
    return sign(line(fr))*sign(line(to));
}

bool test(pII fr1,pII to1,pII fr2,pII to2)
{
    Triad line1(fr1,to1),line2(fr2,to2);
    if(line1.a*line2.b==line2.a*line1.b)
    { //平行的情况
        if(line1(fr2)) return 0; //平行且不共线
        else
        { //共线时比较简单，判断两个线段的x轴或y轴范围有没有相交即可
            if(line1.b)
            { //b不为0，说明不垂直于y轴，可以用x坐标比较
                if(max(fr1.first,to1.first)<=min(fr2.first,to2.first)) return 0;
                if(min(fr1.first,to1.first)>=max(fr2.first,to2.first)) return 0;
            }
            if(line1.a)
            { //a不为0，说明不垂直于x轴
                if(max(fr1.second,to1.second)<=min(fr2.second,to2.second)) return 0;
                if(min(fr1.second,to1.second)>=max(fr2.second,to2.second)) return 0;
            }
            return 1;
        }
    } else
    {
        if(fr1==fr2||fr1==to2||to1==fr2||to1==to2) return 0; //共端点
        if(stand(line1,fr2,to2)<=0&&stand(line2,fr1,to1)<=0) return 1;
        return 0;
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;++i) scanf("%d %d",&edge[i].first,&edge[i].second);
    for(int i=1;i<=n;++i) scanf("%d %d",&point[i].first,&point[i].second);
    int ans=0;
    for(int i=0;i<m-1;++i)
        for(int j=i+1;j<m;++j)
            if(test(point[edge[i].first],point[edge[i].second],
                    point[edge[j].first],point[edge[j].second])) ++ans;
    printf("%d\n",ans);
    return 0;
}

/*=======================================
added at 2019.Feb28 19:27:41	problem:J
判断线段相交模板题
注意防止爆ll
=======================================*/