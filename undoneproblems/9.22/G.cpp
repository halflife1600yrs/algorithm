#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int l;
char str[105];

void sub(int x)
{
    str[l-1]-=x%10;
    if(str[l-1]<'0') str[l-1]+=10,--str[l-2];
    str[l-2]-=x/10;
    int p=l-2;
    while(str[p]<'0')
    {
        str[p-1]-=1;
        str[p]+=10;
        --p;
    }
}

bool check()
{
    if(l<2) return 0;
    if(l==3)
    {
        int ans=100*str[0]+10*str[1]+str[2]-111*'0';
        return !(ans%17);
    }
    sub(5*(str[--l]-'0'));
    str[l]=0;
    return check();
}

int main()
{
    while(scanf("%s",str),str[0]-'0')
    {
        l=strlen(str);
        printf("%d\n",check());
    }
    return 0;
}