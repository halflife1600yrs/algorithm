#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

inline ll cross(pii a,pii b) { return abs(1ll*a.first*b.second-1ll*a.second*b.first); }
int exgcd(int a,int b,int &x,int &y)
{
	if (b == 0) {x = 1;y = 0;return a;}
	int t = exgcd(b,a % b,x,y);
	int x0 = x,y0 = y;
	x = y0;y = x0 - (a / b) * y0;
	return t;
}

int main()
{
    int T;
    scanf("%d",&T);
    int X,Y;
    while(T--)
    {
        scanf("%d %d",&X,&Y);
        if(X<=50000)
        {
            printf("3\n%d 0\n0 %d\n0 %d\n",X,Y-1,Y);
            continue;            
        }
        if(Y<=50000)
        {
            printf("3\n0 %d\n%d 0\n%d 0\n",Y,X-1,X);
            continue;
        }
        int xC,yC;
        int gcd=exgcd(Y,X,xC,yC);
        xC=abs(xC),yC=abs(yC);
        ll s=cross(pii(X,Y),pii(xC,yC));
        if(s<=50000)
        {
            printf("3\n0 0\n%d %d\n%d %d\n",X,Y,xC,yC); //这种情况是gcd越小的时候面积越小
        } else
        {
            printf("4\n0 0\n%d %d\n%d %d\n%d %d\n",X-1,Y,X/gcd,Y/gcd,X,Y-1); //这种情况是gcd越大的时候面积越小
        }
    }
    return 0;
}

/*=======================================
added at 2019.Apr02 12:24:54	problem:CSU2299
exgcd
这题真的想不到啊真的想不到
我好菜啊😭
=======================================*/