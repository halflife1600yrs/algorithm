#include <bits/stdc++.h>

using namespace std;

const int MAXN=300,MAXL=15;
char str[MAXN][MAXL];
int top,lenz[MAXN];

bool check(char* c,int l)
{
    for(int i=0;i<top;++i)
    {
        if(!strcmp(c,str[i]))
        {
            lenz[i]=max(lenz[i],l);
            return 1;
        }
    }
    return 0;
}

int main()
{
    int sup,now;
    scanf("%d%d",&sup,&now);
    char c[MAXL],clean[10];
    int l=1;
    for(int i=top=0;i<now;)
    {
        scanf("%8[\n \r]",clean);
        scanf("%15[Ra-z:]",c);
        if(!strcmp(c,"Re:"))
        {
            ++l;
            continue;
        }
        ++i;
        if(!check(c,l))
        {
            strcpy(str[top],c);
            lenz[top++]=l;
        }
        l=1;
    }
    int ans=0;
    for(int i=0;i<top;++i)
        ans+=lenz[i];
    if(ans>sup) printf("NO\n");
    else printf("YES\n");
    return 0;
}
/*
6 4
Re: Re: Re: Re: hello
Re: hello
world
Re: Re: Re: world
*/
