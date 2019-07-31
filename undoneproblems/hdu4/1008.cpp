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

typedef pair<int, int> pii;
const int MAXN = 1.5e5;
int n, q;
namespace dtree
{
    pii data[20][MAXN];
    int toleft[20][MAXN];
    void build(int fr = 0, int to = n, int depth = 0)
    {
        if(to - fr == 1) return;
        int mid = (fr + to) >> 1;
        int a = fr, b = mid;
        for(int i = fr; i < to; i++)
        {
            toleft[depth][i] = i > fr ? toleft[depth][i - 1] : 0;
            if(data[depth][i].second < mid) //
            {
                data[depth + 1][a++] = data[depth][i];
                ++toleft[depth][i];
            } else
                data[depth + 1][b++] = data[depth][i];
        }
        build(fr, mid, depth + 1);
        build(mid, to, depth + 1);
    }
    int find(int fr, int to, int k, int l = 0, int r = n, int depth = 0)
    {
        if(to - fr == 1) return data[depth][fr].first;
        int mid = (l + r) >> 1, prefix = fr > l ? toleft[depth][fr - 1] : 0;
        int left = toleft[depth][to - 1] - prefix;
        if(left >= k)
            find(l + prefix, l + prefix + left, k, l, mid, depth + 1);
        else
            find(mid + fr - l - prefix, mid + fr - l - prefix + to - fr - left, k - left, mid, r, depth + 1);
    }
}

pii val[MAXN];

bool cmp(const pii& a,const pii& b) { return a.first<b.first; }
// 从小到大排

int CURTIME=1,times[MAXN],vised[MAXN];

inline int get_kth(int l,int r,int k)
{
    if(times[k]==CURTIME) return vised[k];
    times[k]=CURTIME;
    return vised[k]=dtree::find(l,r,k);
}

int bsearch(int l,int r,int p)
{ // 用划分树找区间小于等于p的第一个位置
    // debug2(l,r);
    // debug1(p);
    int fr=1,to=r-l+1,mid;
    int lv=get_kth(l,r,fr),rv=get_kth(l,r,to),mv;
    while(to-fr>1)
    {
        mid=(fr+to)>>1;
        mv=get_kth(l,r,mid);
        // debug2(l,r);
        // debug2(fr,to);
        // debug2(mid,mv);
        // debug2(lv,rv);
        if(mv==p) return mid;
        if(mv<p)
        {
            fr=mid,lv=mv;
        } else 
        {
            to=mid,rv=mv;
        }
    }
    return fr;
}

int work(int l,int r,int p,int k)
{ // 这里已经是开区间
    int i=bsearch(l,r,p),j=i+1; // i是区间内小于等于p的第一个位置
    // debug2(i,j);
    int v1,v2,ans;
    int a;
    for(a=0;a<k&&i>0&&j<=r-l;++a)
    {
        v1=get_kth(l,r,i),v2=get_kth(l,r,j);
        if(abs(p-v1)<=abs(v2-p)) ans=abs(p-v1),--i;//,debug2(i,p-v1),debug2(j,v2-p);
        else ans=abs(v2-p),++j;//,debug2(j,v2);
    }
    while(i>0&&a<k) v1=get_kth(l,r,i--),ans=abs(p-v1),++a;//,debug2(i,p-v1);
    while(j<=r-l&&a<k) v2=get_kth(l,r,j++),ans=abs(v2-p),++a;//,debug2(j,v2-p);
    return ans;
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

void test()
{
    for(int i=1;i<=4;++i) printf("%d ",dtree::find(1,5,i));
    printf("\n");
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T;
    read(T);
    CURTIME=1; // 时间戳
    while(T--)
    {
        read(n),read(q);
        for(int i=0;i<n;++i)
        {
            read(val[i].first);
            val[i].second=i;
            // debug1(val[i].first);
        }
        sort(val,val+n,cmp);
        for(int i = 0; i < n; i++)
        {
            int tmp = val[i].second;
            dtree::data[0][tmp] = pii(val[i].first, i);
        }
        dtree::build();
        // test();
        int l,r,p,k,ans=0;
        for(int i=0;i<q;++i)
        {
            read(l),read(r),read(p),read(k);
            l^=ans,r^=ans,p^=ans,k^=ans;
            if(r-l+1<k)
            {
                debug2(l,r);
                debug1(k);
                printf("111\n");
                return 0;
            }
            ans=work(l-1,r,p,k); // 闭区间转开区间
            printf("%d\n",ans);
            ++CURTIME;
        }
    }
    // cout<<clock()<<endl;
    return 0;
}

/*==================================================================
added at 2019-07-31 16:39:07 1008
2
7 1
10 17 14 57 10 22 57
4 7 56 2
7 2
1 1 1 1 1 1 1
2 6 1 3
1 7 3 6
==================================================================*/