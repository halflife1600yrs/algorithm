#include <bits/stdc++.h>
const int MODE=1e9+7;
const int MAXN=1e5+7;
using namespace std;
typedef long long ll;
struct opera{
    int cnt,l,r;
}opt[MAXN];
int n,m;
int tpach[MAXN],apach[MAXN];
 
inline void add(int& a,int b)
{
    a+=b;
    if(abs(a)>=MODE) a%=MODE;
    if(a<0) a+=MODE;
}
 
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&opt[i].cnt,&opt[i].l,&opt[i].r);
    }
    int t=0;
    tpach[m+1]=1,tpach[1]=-1;
    for(int i=m;i>=1;i--)
    {
        t=(t+tpach[i+1])%MODE;
        if(opt[i].cnt==2){
                add(tpach[opt[i].l],-t);
                add(tpach[opt[i].r+1],t);
        }
        else{
                add(apach[opt[i].l-1],t);
                add(apach[opt[i].r],-t);
        }
    }
    int s=0;
    for(int i=1;i<=n;i++)
    {
        add(s,apach[i-1]);
        printf("%d%c",s,i==n?'\n':' ');
    }
    return 0;
}
 
/*
8 8
1 1 8
2 1 1
2 1 2
2 1 3
2 1 4
2 1 5
2 1 6
2 1 7
*/