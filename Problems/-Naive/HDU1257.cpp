#include <bits/stdc++.h>

using namespace std;

const int MAXN=300000;
int sys[MAXN],top;

int main()
{
    int n,k;
    while(~scanf("%d",&n))
    {
        for(int i=top=0;i<n;++i)
        {
            scanf("%d",&k);
            if(!top)
            {
                sys[top++]=k;
                continue;
            }
            if(k>sys[top-1]) sys[top++]=k;
            else
            {
                for(int j=0;j<top;++j)
                {
                    if(sys[j]==k) break;
                    if(sys[j]>k)
                    {
                        sys[j]=k;
                        break;
                    }
                }
            }
        }
        printf("%d\n",top);
    }
    return 0;
}