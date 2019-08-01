#include <bits/stdc++.h>

using namespace std;

int pows[10000],m[100];
bool ok[10000];
vector<int> ans[100];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int i;
        scanf("%d",&i);
        if(i==1)
        {
            printf("1\n");
            continue;
        }
        {
            memset(ok,0,sizeof(ok));
            for(int j=0;j<100;++j) ans[j].resize(0);
            int pos;
            ans[1].push_back(0);
            for(int j=pows[0]=1;j<10000;++j)
            {
                pows[j]=pows[j-1]*10%i;
                ans[pows[j]].push_back(j);
                if(ans[pows[j]].size()==i)
                {
                    pos=pows[j];
                    break;
                }
            }
            for(int k:ans[pos]) ok[k]=1;//,debug1(k);
            int k=9999;
            while(!ok[k]) --k;
            while(k>=0)
            {
                printf("%c",ok[k]?'1':'0');
                --k;
            }
            printf("\n");
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-01 21:03:25 2019牛客多校第五场A
寻找一个大数使得它本身和各位数之和是n的倍数
事实上用n个n就可以
这里寻找n个位数为1并且其值模n相同的位
==================================================================*/