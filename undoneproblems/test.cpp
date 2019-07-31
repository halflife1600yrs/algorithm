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
const int MAXN = 200005;
int n, q;
namespace dtree
{
    pii data[18][MAXN];
    int toleft[18][MAXN];
    void build(int fr = 0, int to = n, int depth = 0)
    {
        if(to - fr == 1) return;
        // debug2(fr,to);
        int mid = (fr + to) >> 1;
        int a = fr, b = mid;
        for(int i = fr; i < to; i++)
        {
            toleft[depth][i] = i > fr ? toleft[depth][i - 1] : 0;
            if(data[depth][i].second < mid) //
            {
                data[depth + 1][a++] = data[depth][i];
                toleft[depth][i]++;
            } else
                data[depth + 1][b++] = data[depth][i];
        }
        build(fr, mid, depth + 1);
        build(mid, to, depth + 1);
    }
    int find(int fr, int to, int k, int l = 0, int r = n, int depth = 0)
    {
        if(to - fr == 1) return data[depth][fr].first;
        int mid = (l + r) / 2, prefix = fr > l ? toleft[depth][fr - 1] : 0;
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

// int CURTIME=0,times[MAXN],vised[MAXN];

int bsearch(int l,int r,int p)
{ // 用划分树找区间小于等于p的第一个位置
    // debug2(l,r);
    // debug1(p);
    int fr=1,to=r-l+1,mid;
    int lv=dtree::find(l,r,fr),rv=dtree::find(l,r,to),mv;
    while(to-fr>1)
    {
        mid=(fr+to)>>1;
        mv=dtree::find(l,r,mid);
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
        v1=dtree::find(l,r,i),v2=dtree::find(l,r,j);
        if(p-v1<=v2-p) ans=p-v1,--i;//,debug2(i,p-v1),debug2(j,v2-p);
        else ans=v2-p,++j;//,debug2(j,v2);
    }
    while(i>0&&a<k) v1=dtree::find(l,r,i--),ans=p-v1,++a;//,debug2(i,p-v1);
    while(j<=r-l&&a<k) v2=dtree::find(l,r,j++),ans=v2-p,++a;//,debug2(j,v2-p);
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
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int T;
    read(T);
    debug1(T);
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
            // l^=ans,r^=ans,p^=ans,k^=ans;
            ans=work(l-1,r,p,k); // 闭区间转开区间
            printf("%d\n",ans); 
        }
    }
    cout<<clock()<<endl;
    return 0;
}