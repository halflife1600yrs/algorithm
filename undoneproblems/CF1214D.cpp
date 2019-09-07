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

const int MAXN=1e6+5;
char land[MAXN];
int n,m;
bool vis[MAXN],ans[MAXN];

bool dfs(int pos)
{
    // debug1(pos);
    if(pos==n*m-1) return 1;
    vis[pos]=1;
    ans[pos]=0;
    if(pos%m<m-1&&pos+1<n*m&&land[pos+1]=='.'&&!vis[pos+1])
        ans[pos]|=dfs(pos+1);
    if(ans[pos]) return 1;
    if(pos+m<n*m&&land[pos+m]=='.'&&!vis[pos+m])
        ans[pos]|=dfs(pos+m);
    return ans[pos];
}

int main()
{
    scanf("%d %d",&n,&m);
    // debug2(n,m);
    for(int i=0;i<n;++i)
        scanf("%s",land+i*m);
    dfs(1),dfs(m);
    if(n==1||m==1) printf(ans[1]?"1\n":"0\n");
    else if(ans[1]==1&&ans[m]==1) printf("2\n");
    else if(ans[1]==0&&ans[m]==0) printf("0\n");
    else printf("1\n");
    return 0;
}

/*==================================================================
added at 2019-09-04 19:14:05 CF1214D
5 6
......
......
......
..####
..#...
8 6
......
#.....
.#....
..#...
...#..
....#.
.....#
......

==================================================================*/