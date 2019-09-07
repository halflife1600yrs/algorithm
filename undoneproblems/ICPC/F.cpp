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

const int MAXV=205,INF=0x7f7f7f7f;
typedef long long ll;
typedef pair<int,int> pii;
int V,Q,land[MAXV][MAXV][MAXV];
pii city[MAXV];

void floyed()
{
    for(int k=1;k<=V;++k)
        for(int i=1;i<=V;++i)
            for(int j=1;j<=V;++j)
                land[k][i][j]=min(land[k-1][i][j],
                    land[k-1][i][city[k].second]+land[k-1][city[k].second][j]);
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

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T;
    read(T);
    for(int _=1;_<=T;++_)
    {
        read(V),read(Q);
        for(int i=1;i<=V;++i) read(city[i].first),city[i].second=i;
        sort(city+1,city+V+1);
        for(int i=1;i<=V;++i)
            for(int j=1;j<=V;++j)
                read(land[0][i][j]);
        floyed();
        printf("Case #%d: \n",_);
        for(int i=0,st,en,l,pos;i<Q;++i)
        {
            read(st),read(en),read(l);
            pos=(lower_bound(city+1,city+V+1,pii(l+1,0))-city)-1;
            // debug1(pos);
            printf("%d\n",land[pos][st][en]);
        }
    }
    return 0;
}