#include <bits/stdc++.h>

using namespace std;

inline void judge(bool i)
{
    if(i) printf("Alice\n");
    else printf("Bob\n");
}

int main()
{
    int n,q;
    scanf("%d %d",&n,&q);
    bool state=(n-1)&1;
    for(int i=0,x,y;i<q;++i)
    {
        scanf("%d %d",&y,&x);
        y=n-y,x=n-x;
        // debug2(x,y);
        if((y&1)||(x&1)) judge(state); // 原来就是必胜点
        else if(x==y) judge(state); // 修改在对角线上时只影响那一行
        else if(x==n-1||x==n-2||x==n-3) judge(!state); // 不在对角线上使会影响三列
        else judge(state);
    }
    return 0;
}

/*=======================================
added at 2019.May28 12:57:16	problem:NK847E
7 1
5 3

5 1
5 3

5 1
5 1
博弈论的题目
强制令一点不可选时，就相当于强制使这点变为必胜点
=======================================*/