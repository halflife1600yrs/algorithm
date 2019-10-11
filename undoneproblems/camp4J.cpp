#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=505;
const double EPS=1e-5,STEP=0.1;
int x[MAXN],y[MAXN],tag[2][MAXN];
int G[2*MAXN][2*MAXN],b[2*MAXN];
double v[2*MAXN],d[2*MAXN];

double GradFallMethod(int n)
{ // 计算二次函数x'GX+b'x的最小值,其梯度为2Gx+b
    while(1)
    {
        double check=0.0;
        for(int i=1;i<=n;++i)
        {
            d[i]=b[i];
            for(int j=1;j<=n;++j)
                d[i]+=2*G[i][j]*v[j];
            // printf("%.4lf ",d[i]);
            double tmp=STEP*d[i];
            v[i]-=tmp;
            check+=tmp;
        }
        // puts("");
        // for(int i=1;i<=2*n;++i) printf("%.4lf ",v[i]);
        // printf("%.5lf\n",sqrt(abs(check)));
        if(abs(check)<EPS*EPS) break;
        // debug1(check);
    }
    // for(int i=1;i<=2*n;++i) printf("%.4lf ",v[i]);
    // puts("");
    double ans=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            ans+=G[i][j]*v[i]*v[j];
        ans+=b[i]*v[i];
    }
    return ans;
}

int main()
{
    int n,c=0;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d %d",&x[i],&y[i]);
        c+=x[i]*x[i]+y[i]*y[i];
    }
    for(int i=0;i<n;++i) scanf("%d",&tag[0][i]);
    for(int i=0;i<n;++i) scanf("%d",&tag[1][i]);
    int t1,t2;
    for(int i=0;i<n;++i)
    {
        t1=tag[0][i],t2=n+tag[1][i];
        G[t1][t1]+=2,++G[t2][t2],--G[t1][t2],--G[t2][t1];
        b[t1]-=2*x[i];
    }
    // for(int i=1;i<=2*n||(puts(""),0);++i,puts(""))
    //     for(int j=1;j<=2*n;++j) printf("%d ",G[i][j]);
    // for(int i=1;i<=2*n;++i) printf("%d ",b[i]);
    // puts("");
    double ans=GradFallMethod(2*n);
    fill(b,b+n+5,0);
    for(int i=0;i<n;++i)
        b[tag[0][i]]-=2*y[i];
    // for(int i=1;i<=2*n;++i) printf("%d ",b[i]);
    // puts("");
    ans+=GradFallMethod(2*n);
    printf("%.6lf\n",ans+c);
    return 0;
}