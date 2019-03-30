#include <bits/stdc++.h>

using namespace std;

const bool BLACK=true;
const bool WHITE=false;
const int MAXN=26;
int ans[MAXN],f[MAXN],g[MAXN];
int stepLeft;

void trans(int lot1,int lot2,bool color);
void exhanoi1(int h);
void exhanoi2(int h,int lot1,int lot2,int lot3,int lot4,bool color);
void hanoi(int h,int lot1,int lot2,int lot3,bool color);
void work(int h);

inline void printAns(int lot1,int lot2,bool color)
{
    printf("MOVE %s FLOOR FROM LOT %d to LOT %d\n",color?"black":"white",lot1,lot2);
    return;
}

int main()
{
    ans[1]=3,f[1]=2,g[1]=1;
    for(int i=2;i<=25;i++)
    {
        f[i]=(g[i-1]<<2)+2;
        g[i]=(g[i-1]<<1)+1;
        ans[i]=(f[i-1]<<1)+(g[i-1]<<1)+3;
    }
    for(int T,_=scanf("%d",&T),n;T--;)
    {
        scanf("%d %d %d",&_,&n,&stepLeft);
        printf("%d %d ",_,ans[n]);
        work(n);
    }
    return 0;
}

void trans(int lot1,int lot2,bool color)
{ //从lot1运到lot2,color 0是白1是黑
    if(!stepLeft) return;
    if(stepLeft==1) printAns(lot1,lot2,color);
    if(stepLeft>=1) --stepLeft;
}

void exhanoi1(int h)
{
    if(!stepLeft) return;
    if(h==1)
    {
        trans(1,2,WHITE);
        trans(3,1,BLACK);
        return;
    }
    if(stepLeft>f[h])
    {
        stepLeft-=f[h];
        return;
    }
    exhanoi1(h-1);
    if(h&1)
    {
        trans(1,2,WHITE);
        hanoi(h-1,3,2,1,WHITE);
        trans(3,1,BLACK);
        hanoi(h-1,4,1,3,BLACK);
    } else
    {
        trans(3,4,BLACK);
        hanoi(h-1,1,4,3,BLACK);
        trans(1,3,WHITE);
        hanoi(h-1,2,3,1,WHITE);
    }
}

void exhanoi2(int h,int lot1,int lot2,int lot3,int lot4,bool color)
{ //h是高度,从lot1/lot2的两堆移到lot2/lot3,lot4是中转站,color是lot2的颜色要先移
// lot2是公有的,
    if(!stepLeft) return;
    if(h==1)
    {
        trans(lot2,lot3,color);
        trans(lot1,lot2,!color);
    }
    if(stepLeft>f[h])
    {
        stepLeft-=f[h];
        return;
    }
    hanoi(h-1,lot2,lot4,lot3,color);
    trans(lot2,lot3,color);
    hanoi(h-1,lot1,lot3,lot2,!color);
    trans(lot1,lot2,!color);
    exhanoi2(h-1,lot4,lot3,lot2,lot1,!color);
}

void hanoi(int h,int lot1,int lot2,int lot3,bool color)
{ //h是高度,lot1->lot2,lot3是中转站
    if(!stepLeft) return;
    if(h==1)
    {
        trans(lot1,lot2,color);
        return;
    }
    if(stepLeft>g[h])
    {
        stepLeft-=g[h];
        return;
    }
    hanoi(h-1,lot1,lot3,lot2,color);
    trans(lot1,lot2,color);
    hanoi(h-1,lot3,lot2,lot1,color);
}

void work(int h)
{
    if(h==1)
    {
        trans(1,2,WHITE);
        trans(3,1,BLACK);
        trans(2,3,WHITE);
        return;
    }
    if(h&1)
    {
        exhanoi1(h-1);
        trans(1,2,WHITE);
        hanoi(h-1,3,2,1,WHITE);
        trans(3,1,BLACK);
        hanoi(h-1,2,1,3,WHITE);
        trans(2,3,WHITE);
        exhanoi2(h-1,4,1,3,2,WHITE);
    } else
    {
        exhanoi1(h-1);
        trans(3,4,BLACK);
        hanoi(h-1,1,4,3,BLACK);
        trans(1,3,WHITE);
        hanoi(h-1,4,3,1,BLACK);
        trans(4,1,BLACK);
        exhanoi2(h-1,2,3,1,4,BLACK);
    }
}

/*=======================================
added at 2019.Mar20 12:39:18	problem:CSU2271
分情况讨论+dfs
一定要注意题目中白块先移的约束
=======================================*/