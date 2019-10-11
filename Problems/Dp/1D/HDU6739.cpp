#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
const char need[10][4]={
"000", //Y
"001", //V
"002", //G
"111", //C
"011", //X
"112", //Z
"222", //T
"022", //F
"122", //D
"012"  //B
};
int step[27][27],state[256][6],dp[2][27];
char str[MAXN];

int main()
{
    const char name[11]="YVGCXZTFDB";
    for(int i=0;i<10;++i)
    {
        state[name[i]][0]=need[i][0]+3*need[i][1]+9*need[i][2]-13*'0';
        state[name[i]][1]=need[i][0]+3*need[i][2]+9*need[i][1]-13*'0';
        state[name[i]][2]=need[i][1]+3*need[i][0]+9*need[i][2]-13*'0';
        state[name[i]][3]=need[i][1]+3*need[i][2]+9*need[i][0]-13*'0';
        state[name[i]][4]=need[i][2]+3*need[i][0]+9*need[i][1]-13*'0';
        state[name[i]][5]=need[i][2]+3*need[i][1]+9*need[i][0]-13*'0';
    }
    int a,b,c,d;
    for(int i=0;i<27;++i)
    {
        for(int j=0;j<27;++j)
        {
            a=i%3,b=i%9/3;
            d=j/9,c=(j%9)/3;
            if(j==i) step[i][j]=0;
            else if(a==c&&b==d) step[i][j]=1;
            else if(a==d) step[i][j]=2;
            else step[i][j]=3;
        }
    }
    while(~scanf("%s",str))
    {
        int l=strlen(str);
        bool pos=1;
        for(int i=0;i<6;++i) dp[0][state[(int)str[0]][i]]=3;
        int x,y;
        for(int i=1;i<l;++i)
        {
            for(int k=0;k<6;++k)
            {
                x=state[(int)str[i]][k];
                dp[pos][x]=0x7f7f7f7f;
                for(int j=0;j<6;++j)
                {
                    y=state[(int)str[i-1]][j];
                    dp[pos][x]=min(dp[pos][x],dp[!pos][y]+step[y][x]);
                }
            }
            pos=!pos;
        }
        int ans=0x7f7f7f7f;
        for(int i=0;i<6;++i)
            ans=min(ans,dp[!pos][state[str[l-1]][i]]);
        printf("%d\n",ans+l);
    }
    return 0;
}

/*==================================================================
added at 2019-09-28 19:41:20 2019CCPC秦皇岛I
模拟的内容比较多,dp的内容相对少一点
数组又开小了
==================================================================*/