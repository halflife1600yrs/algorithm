#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int a[sz], b[sz];

int LCS(int* a, int* b, int lenz)
{

}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
    printf("%d\n", LCS(a, b, n));
    return 0;
}