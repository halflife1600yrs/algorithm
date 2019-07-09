#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,l;
    scanf("%d %d",&l,&n);
    int maxi=0,mini=0;
    for(int i=0,pos;i<n;++i)
    {
        scanf("%d",&pos);
        maxi=max(maxi,max(pos,l+1-pos));
        mini=max(mini,min(pos,l+1-pos));
    }
    printf("%d %d\n",mini,maxi);
    return 0;
}

/*==================================================================
added at 2019-07-09 09:34:49 P1007
很巧妙的贪心题
互相碰撞之后掉头其实就相当于穿过继续走
所以不能相交的路径其实就等同于可相交的路径
==================================================================*/