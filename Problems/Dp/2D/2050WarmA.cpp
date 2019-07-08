#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const double limit=1e-7;
ll p1[100],p2[100];
double dp[2][20];

int main()
{
   int n,m,y,T;
   scanf("%d",&T);
   while(T--)
   {
      scanf("%d %d %d",&n,&m,&y);
      int sum=n+m;
      double e=0,p=1.0/sum,diff=1.0*m/sum;
      for(int i=0;i<n;++i) scanf("%d",&p1[i]),e+=p1[i]*p,dp[0][i]=p1[i];
      for(int i=0;i<m;++i) scanf("%d",&p2[i]),dp[0][i+n]=p2[i];
      bool pos=1;
      for(int i=1;i<(1<<sum)&&p>limit;++i)
      {
         p*=diff;
         for(int i=0;i<n;++i)
         {
            dp[pos][i]=0;
            for(int j=0;j<m;++j) dp[pos][i]+=dp[!pos][j+n]+p1[i];
            dp[pos][i]/=m;
            e+=dp[pos][i]*p;
         }
         for(int i=0;i<m;++i)
         {
            dp[pos][i+n]=0;
            for(int j=0;j<m;++j) dp[pos][i+n]+=dp[!pos][j+n]+p2[i];
            dp[pos][i+n]/=m;
         }
         pos=!pos;
      }
      if(e<=y) printf("Go\n");
      else printf("Wait\n");
   }
   return 0;
}

/*=======================================
added at 2019.Apr11 19:20:29	problem:2050A
期望dp
其实这道题化为两条路就可以过了
=======================================*/