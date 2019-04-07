#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=2e5+5,MAXM=1e5+5;
int up[MAXN],down[MAXN];
pii arms[MAXM];

bool cmp(pii a,pii b) { return a.first<b.first; }

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;++i) scanf("%d %d",&arms[i].first,&arms[i].second);
    sort(arms,arms+m,cmp);
    for(int i=0,pos;i<m;++i)
    {
        pos=arms[i].second;
        down[pos]=down[pos+1]+1;
        up[pos+1]=up[pos]+1;
    }
    for(int i=1;i<n;++i) printf("%d ",up[i]+down[i]+1);
    printf("%d\n",up[n]+down[n]+1);
    return 0;
}

/*=======================================
added at 2019.Apr02 15:46:02	problem:CSU2293

=======================================*/