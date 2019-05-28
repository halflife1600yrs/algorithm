#include <bits/stdc++.h>

using namespace std;

char m[3][3],clear[5];

int check()
{
    int wnum=0;
    for(int k=0;k<3;++k)
    {
        if(m[k][k]=='W') ++wnum;
        if(m[k][k]=='B')
        {
            wnum=0;
            break;
        }
    }
    if(wnum==2) return 1;
    wnum=0;
    for(int k=0;k<3;++k)
    {
        if(m[2-k][k]=='W') ++wnum;
        if(m[2-k][k]=='B')
        {
            wnum=0;
            break;
        }
    }
    if(wnum==2) return 1;
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(m[i][j]=='#')
            {
                wnum=0;
                for(int k=0;k<3;++k)
                    if(m[i][k]=='W') ++wnum;
                if(wnum==2) return 1;
                wnum=0;
                for(int k=0;k<3;++k)
                    if(m[k][j]=='W') ++wnum;
                if(wnum==2) return 1;
            }
        }
    }
    return 0;
}

int dfs()
{
    int ans=0;
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j)
            if(m[i][j]=='W')
            {
                m[i][j]='#';
                if(!check()) return 0;
                m[i][j]='W';
            }
    return 1;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
            {
                scanf("%4[ \n\r]",clear);
                scanf("%1[WB#]",&m[i][j]);
            }
        if(check())
        {
            if(dfs()) printf("Alice\n");
            else printf("Emmm\n");
        } else printf("Bob\n");
    }
    return 0;
}

/*=======================================
added at 2019.May03 20:23:56	problem:B
3
W#W
BBB
W#W

W#W
B##
WBW

W#W
B#W
WB#
=======================================*/