#include <bits/stdc++.h>

using namespace std;

const int pows[12]={1,2,4,8,16,32,64,128,256,512,1024};

int read()
{
    char c;
    int ans=0;
    bool get=0;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans|=pows[c-'0'],get=1;
        else if(get) break;
        else continue;
    }
    // debug1(ans);
    return ans;
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        // debug1(n);
        set<int> s;
        for(int i=0;i<n;++i)
            s.insert(read());
        printf("%d\n",s.size());
    }
    return 0;
}

/*==================================================================
added at 2019-08-09 12:14:31	B
5
132
42
3312
43
24424
3
222
22
2

==================================================================*/