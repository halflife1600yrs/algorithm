#include <bits/stdc++.h>

using namespace std;

int n,m;

int player(int team1,int team2)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {

        }
    }
}

int team()
{
    for(int i=0;i<m;++i)
    {
        for(int j=i+1;j<m;++j)
        {
            player(i,j);
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    team();
    return 0;
}