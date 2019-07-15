#include <bits/stdc++.h>

using namespace std;

const int MAXN=30,STATE=2e7+5;
int cow[MAXN];
bitset<STATE> s1;

int main()
{
    int n,h;
    scanf("%d%d",&n,&h);
    s1.reset();
    for(int i=0;i<n;++i)
    {
        scanf("%d",&cow[i]);
        if(i)
            s1|=s1<<cow[i];
        else s1[0]=s1[cow[0]]=1;
    }
    int pos=-h;
    for(int i=h;;++i)
    {
        if(s1[i])
        {
            pos+=i;
            break;
        }
    }
    printf("%d\n",pos);
    return 0;
}