#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pII;
const int MAXN = 5e3+5;
int cow[MAXN];

struct Quee
{
    int data[MAXN],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} Q;

int LIS(int* aim,int lenz)
{
    Q.top=0;
    Q.add(aim[0]);
    for(int i=1;i<lenz;++i)
    {
        if(aim[i]>Q[Q.top-1]) Q.add(aim[i]);
        else
        {
            int l=0,r=Q.top,mid;
            while(r-l>1)
            {
                mid=(r+l)/2;
                if(Q[mid]>=aim[i]) r=mid;
                else if(Q[mid]<aim[i]) l=mid;
            }
            if(Q[l]<aim[i]) Q[r]=aim[i];
            else Q[l]=aim[i];
        }
    }
    return Q.top;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&cow[i]);
    printf("%d\n",LIS(cow,n));
    return 0;
}

/*==================================================================
added at 2019-07-06 14:37:22 Problem:NK984D.cpp
LIS模板题
==================================================================*/