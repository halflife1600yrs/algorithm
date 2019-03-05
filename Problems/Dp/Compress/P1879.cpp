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
const int MAXSTATE=1<<12;
const int MODE=1e9;
bool field[13][13];
int unfer[13];
ll dp[13][MAXSTATE];
struct Quee
{
    short data[MAXSTATE];
    int top;
    void add(short x) { data[top++]=x; }
    short& operator[](int x) { return data[x]; }
} Q;

void init(int x)
{
    Q.top=0;
    for(int i=0,end=1<<x;i<end;++i)
        if(((i&i<<1)==0)&&((i&i>>1)==0)) Q.add(i);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i)
    {
        unfer[i]=0;
        for(int j=0;j<m;++j)
        {
            scanf("%d",&field[i][j]);
            if(!field[i][j]) unfer[i]+=1<<j; //记录不可用状态
        }
    }
    init(m);
    // debug1(Q.top);
    for(int i=0;i<Q.top;++i)
        if(!(Q[i]&unfer[0])) dp[0][Q[i]]=1;
    for(int i=1;i<n;++i)
        for(int j=dp[i][Q[j]]=0;j<Q.top;++j)
            if(!(Q[j]&unfer[i]))
                for(int k=0;k<Q.top;++k)
                    if(!(Q[j]&Q[k])) dp[i][Q[j]]=(dp[i][Q[j]]+dp[i-1][Q[k]])%MODE;
    ll ans=0;
    for(int i=0;i<Q.top;++i) ans=(dp[n-1][Q[i]]+ans)%MODE;
    printf("%lld\n",ans);
    return 0;
}