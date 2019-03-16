#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> Pii;
const int MAXN=2e5+5;
char str[MAXN];
int top;

int main()
{
    int n;
    for(int i=1;str[i-1]!='\n';++i) str[i]=getchar();
    char c;
    int maxi=0;
    for(int i=1,last=0,lenz=0,end=strlen(str+1);i<end;++i)
    {
        c=getchar();
        if(str[i]!=c)
        {
            maxi=max(maxi,lenz);
            lenz=0;
            continue;
        }
        ++lenz;
    }
    printf("%d\n",(maxi+1)*(maxi+1)-1);
    return 0;
}