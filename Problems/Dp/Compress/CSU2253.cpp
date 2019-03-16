#include <bits/stdc++.h>

using namespace std;

int n,m,k;
double dp[2][462][462];
const int power[7]={0,1,10,100,1000,10000,100000};
// 状压dp
// 对两个玩家分别保存每个血量的怪物有几只，压缩为一个6进制的数
// 比如剩下1个6血怪1个5血怪3个1血怪，状态为110003
// power[i]-血量为i的怪的状态值
// 然后将状态压入数组（Q1和Q2），枚举在Q中的下标进行dp
// dp[i][s1][s2]表示第i发，打完之后我方的状态为s1,敌方状态为s2的概率
// 状态转移为dp[ i ][ s1-power[i]+power[i-1] ][ s2 ]=dp[i-1][s1][s2]
struct
{
    int state[462],hpSum[462],alive[462],top;
    // 保存状态，此状态下怪物总血量，怪物总数（用状态算也行但是会慢）
    int all[7],maxState;
    int shash[500005]; // 用hash表建立状态与队列位置的关联
    void init(int depth,int remain)
    {
    // 生成一个玩家所有血量-怪物的合法状态，相当于将n个怪兽放进0-6血的六个抽屉中
    // 用搜索初始化表，depth表示目前放到第几个血量值，remain表示还有几个怪物没放
        if(depth==6)
        {
            all[6]=remain;
            state[top]=hpSum[top]=alive[top]=0;
            for(int i=1;i<7;++i)
                state[top]+=all[i]*power[i],hpSum[top]+=all[i]*i,alive[top]+=all[i];
            if(state[top]<=maxState) // 只保存血量比初始状态少的情况
            {
                shash[state[top]]=top;
                top++;
            }
            return;
        }
        for(int i=0;i<=remain;++i)
        {
            all[depth]=i;
            init(depth+1,remain-i);
        }
    }
} Q1,Q2;

inline int digit(int x,int pos) { return (x/power[pos])%10; }
// 给定一个状态，求有pos血的怪物有几个

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    int maxHp1=0,maxHp2=0;
    Q1.top=Q2.top=0;
    for(int i=0,j;i<n;++i) scanf("%d",&j),Q1.maxState+=power[j],maxHp1+=j;
    for(int i=0,j;i<m;++i) scanf("%d",&j),Q2.maxState+=power[j],maxHp2+=j;
    // 输入

    Q1.init(0,n),Q2.init(0,m);
    for(int i=0,num,newState;i<6;++i)
    {
        num=digit(Q1.maxState,i+1);
        if(num)
        {
            newState=Q1.maxState-power[i+1]+power[i]; // 打了一个怪物后它血量减一，相当于把一个i+1血的怪替换为i血
            dp[0][Q1.shash[newState]][Q2.shash[Q2.maxState]]+=1.0*num/(n+m); // 打到i+1血的怪的概率为i+1血的怪数除总怪数
        }
    }
    for(int i=0,num,newState;i<6;++i)
    {
        num=digit(Q2.maxState,i+1);
        if(num)
        {
            newState=Q2.maxState-power[i+1]+power[i];
            dp[0][Q1.shash[Q1.maxState]][Q2.shash[newState]]+=1.0*num/(n+m);
        }
    }
    // 初始化

    bool pos=1;
    for(int i=1,tot;i<k&&i<maxHp1+maxHp2;++i,pos=!pos) // 打到全部怪死就停止
    {
        for(int s1=0,state1;s1<Q1.top;++s1) // 枚举我方状态
        {
            if(Q1.hpSum[s1]<maxHp1-i) continue; // 剪枝，我方的怪血量减少一定小于等于已经造成的伤害
            state1=Q1.state[s1];
            for(int s2=0,state2;s2<Q2.top;++s2) //枚举敌方状态
            {
                if(Q2.hpSum[s2]+Q1.hpSum[s1]!=maxHp1+maxHp2-i) continue; // 再剪枝，两方血量合一定等于总血量减去伤害
                state2=Q2.state[s2];
                tot=Q1.alive[s1]+Q2.alive[s2];
                for(int j=0,num,newState;j<6;++j) //枚举打到我方1-6血怪
                {
                    num=digit(state1,j+1);
                    if(num)
                    {
                        newState=state1-power[j+1]+power[j];
                        dp[pos][Q1.shash[newState]][s2]+=dp[!pos][s1][s2]*num/tot;
                    }
                }
                for(int j=0,num,newState;j<6;++j) //枚举打到敌方1-6血怪
                {
                    num=digit(state2,j+1);
                    if(num)
                    {
                        newState=state2-power[j+1]+power[j];
                        dp[pos][s1][Q2.shash[newState]]+=dp[!pos][s1][s2]*num/tot;
                    }
                }
            }
        }
    }
    double ans=0;
    for(int i=0,j=Q2.shash[0];i<Q1.top;++i) // 答案为敌方全死（状态为0）我方所有状态的概率之和
    {
        if(Q1.hpSum[i]!=max(0,maxHp1+maxHp2-k)) continue;
        ans+=dp[min(k-1,maxHp1+maxHp2-1)&1][i][j];
    }
    printf("%.8lf\n",ans);
    return 0;
}

/*=======================================
added at 2019.Mar13 20:48:29	problem:CSU2253
十分致命地忽略了一个情况，十分致命地犯了一个语法错误
导致将近三个小时才写完这题
值得反思值得反思
=======================================*/