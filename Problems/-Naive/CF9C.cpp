#include <bits/stdc++.h>

using namespace std;

int limit[800];
const int pows[10]={1,10,100,1000,(int)1e4,(int)1e5,(int)1e6,(int)1e7,(int)1e8};

int main()
{
    for(int i=1;i<(1ll<<9);++i)
    {
        limit[i]=0;
        for(int j=0;j<=8;++j)
            if(i&(1ll<<j))
                limit[i]+=pows[j];
    }
    int n;
    scanf("%d",&n);
    if(n>=1e9) printf("%d\n",512);
    else printf("%d\n",upper_bound(&limit[1],&limit[1<<9],n)-&limit[1]);
    return 0;
}