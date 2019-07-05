#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const bool B=0,W=1;
int land[8][8];
int nums[2];
struct Quee
{
    pii data[64];
    int t;
    void add(pii x) { data[t++]=x; }
    pii& operator[](int x) { return data[x]; }
} orders[2];

void printLand()
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            switch (land[i][j])
            {
                case B: printf("B"); break;
                case W: printf("W"); break;
                default: printf("."); break;
            }
        }
        printf("\n");
    }
}

void put(int x,int y,bool co)
{
    land[x][y]=co;
    ++nums[co];
}

bool change(int x,int y,pii dir,bool co)
{
    x+=dir.first,y+=dir.second;
    if(x==-1||x==8||y==-1||y==8) return 0; // 地图外
    if(land[x][y]!=!co)
    {
        return 0; // 直接碰到我方棋子或空点
    }
    for(int i=x,j=y;i!=-1&&i!=8&&j!=-1&&j!=8;i+=dir.first,j+=dir.second)
    {
        if(land[i][j]==-1) return 0; // 碰到空点
        if(land[i][j]==co) // 碰到我方棋子，把中间夹的变成我方
        {
            for(;x!=i||y!=j;x+=dir.first,y+=dir.second)
            {
                --nums[!co];
                put(x,y,co);
            }
            return 1;
        }
    }
    return 0; // 一直都没有找到我方棋子
}

bool check(int pos,bool co)
{
    if(pos==64) return 1;
    int x=orders[co][pos].first,y=orders[co][pos].second;
    if(land[x][y]!=-1) return 0;
    bool ans=0; // 只要8个方向有一个可以放就行
    ans|=change(x,y,pii(1,0),co);
    ans|=change(x,y,pii(-1,0),co);
    ans|=change(x,y,pii(0,1),co);
    ans|=change(x,y,pii(0,-1),co);
    ans|=change(x,y,pii(1,1),co);
    ans|=change(x,y,pii(1,-1),co);
    ans|=change(x,y,pii(-1,1),co);
    ans|=change(x,y,pii(-1,-1),co);
    if(ans) put(x,y,co);
    return ans;
}

int main()
{
    memset(land,-1,sizeof(land));
    nums[0]=nums[1]=0;
    for(int i=0,pos;i<8;++i)
        for(int j=0;j<8;++j)
        {
            scanf("%d",&pos);
            --pos;
            orders[0].add(pii(pos/8,pos%8));
        }
    for(int i=0,pos;i<8;++i)
        for(int j=0;j<8;++j)
        {
            scanf("%d",&pos);
            --pos;
            orders[1].add(pii(pos/8,pos%8));
        }
    put(3,3,W);
    put(4,4,W);
    put(3,4,B);
    put(4,3,B);
    while(1)
    {
        int nxt[2]={0,0};
        while(!check(nxt[0],B)) { ++nxt[0]; }
        if(nums[0]==0||nums[1]==0) break;
        while(!check(nxt[1],W)) { ++nxt[1]; }
        if(nxt[0]==64&&nxt[1]==64) break;
        if(nums[0]==0||nums[1]==0) break;
    }
    printLand();
    return 0;
}