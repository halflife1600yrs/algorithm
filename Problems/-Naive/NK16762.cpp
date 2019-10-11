#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
int num[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&num[i]);
    vector<int> v;
    for(int i=31;i>=0;--i)
    {
        bool able[31]={};
        v=vector<int>();
        for(int j=0;j<n;++j)
        {
            if(num[j]&(1<<i))
            {
                v.push_back(num[j]);
                for(int k=0;k<i;++k)
                    if(!(num[j]&(1<<k))) able[k]=1;
            }
        }
        bool flag=1;
        for(int j=0;j<i;++j)
            if(!able[j])
            {
                flag=0;
                break;
            }
        if(flag) break;
    }
    printf("%d\n",v.size());
    if(v.size())
    {
        for(int i=0;i<v.size()-1;++i)
            printf("%d ",v[i]);
        printf("%d\n",*v.rbegin());
    }
    return 0;
}

/*==================================================================
added at 2019-09-26 19:53:55 NK16762
水题,枚举答案
不知道为什么以前没过
==================================================================*/