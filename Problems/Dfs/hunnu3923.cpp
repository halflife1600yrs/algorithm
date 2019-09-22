#include <bits/stdc++.h>

using namespace std;

const int MAXN=55;
char str[MAXN];
bool vis[100];
int l,ans,num[MAXN][2];

void dfs(int pos)
{
    if(pos==l)
    {
        ++ans;
        return;
    }
    if(!vis[num[pos][0]])
    {
        vis[num[pos][0]]=1;
        dfs(pos+1);
        vis[num[pos][0]]=0;
    }
    if(num[pos][0]&&pos<l-1&&!vis[num[pos][1]])
    {
        vis[num[pos][1]]=1;
        dfs(pos+2);
        vis[num[pos][1]]=0;
    }
}

int main()
{
    while(~scanf("%s",str))
    {
        l=strlen(str);
        for(int i=0;i<l;++i)
        {
            num[i][0]=str[i]-'0';
            num[i][1]=num[i][0]*10+str[i+1]-'0';
        }
        ans=0;
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-09-18 19:28:38 2019省赛E
dfs
乍一看好像复杂度很高但是仔细一想最多只有10个1,所以复杂度应该是C(10,30)
==================================================================*/