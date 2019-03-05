#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7;
const int MAXSTATE=1<<15;
char state[15];
ll dp[15][MAXSTATE][15];
struct Quee
{
    int data[6450],top;
    Quee():top(0) {}
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} Q[14];
//Q[i]存的是用了i+1个数的状态
void init(int x)
{
    int tmp;
    for(int i=1;i<(1<<x)-1;++i)
    { //不需要算0000和1111
        tmp=0;
        for(int j=1;j<(1<<x);j<<=1)
            if(i&j) ++tmp;
        Q[tmp-1].add(i);
    }
}

inline int twice(int x) { return ((x+1)<<1)-1; }
inline int half(int x) { return ((x+1)>>1)-1; }
inline int pos(int x) { return 1<<x; }

int main()
{
    int n;
    scanf("%d %s",&n,state);
    init(n);
    for(int i=0;i<Q[0].top;++i) dp[0][ Q[0][i] ][i]=1;
    for(int i=1;i<n;++i) //i为层数，表示用了i+1个数
        for(int j=0,lastState;j<Q[i-1].top;++j)
        { //枚举上层状态
            lastState=Q[i-1][j];
            for(int k=0,curState;k<n;++k)
            { //枚举当前要填的数
                curState=pos(k);
                if(curState&lastState) continue; //如果被选过就不算
                if(state[i-1]=='1')
                {
                    if(twice(k)<n&&(pos(twice(k))&lastState))
                        dp[i][curState|lastState][k]+=dp[i-1][lastState][twice(k)];
                    if((k&1)&&(pos(half(k))&lastState))
                        dp[i][curState|lastState][k]+=dp[i-1][lastState][half(k)];
                    dp[i][curState|lastState][k]%=MODE;
                } else
                    for(int l=lastState,m=0;l;l>>=1,++m)
                        if(l&1)
                        {
                            if((k&1)&&m==half(k)) continue;
                            if(m==twice(k)) continue;
                            dp[i][curState|lastState][k]+=dp[i-1][lastState][m];
                            dp[i][curState|lastState][k]%=MODE;  
                        }
            }
        }
    ll ans=0;
    for(int i=0,fullState=(1<<n)-1;i<n;++i)
        ans=(ans+dp[n-1][fullState][i])%MODE;
    printf("%lld\n",ans);
    return 0;
}

/*=======================================
added at 2019.Feb27 16:32:04	problem:ff
状压dp
dp[i][s][k]，i是层数
s状态保存每个数是否被选取
k是当前要填的数
注意一下数字下标的偏移就好了
=======================================*/