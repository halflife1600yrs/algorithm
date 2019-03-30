#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> Pii;
struct Quee
{
    Pii data[100];
    int top;
    void add(Pii x) { data[top++]=x; }
    Pii& operator[](int x) { return data[x]; }
} blank;
int bhash[10][10];
int matrix[10][10];
int top; //矩阵行数
double A[100][100],B[100];
bool free[100];

void generate()
{
    top=0;
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
        {
            if(matrix[i][j]==-1) A[top][bhash[i][j]]=1;
            if(matrix[j][i]==-1) A[top+1][bhash[i][j]]=1;
            B[top]=B[top+1]=10;
            top+=2;
        }
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            if(matrix[i][j]>0)
            {
                B[top]=matrix[i][j];
                A[top][bhash[i-1][j]]=(i>0),A[top][bhash[i][j-1]]=(j>0);
                A[top][bhash[i+1][j]]=(i<9),A[top][bhash[i][j+1]]=(j<9);
                A[top][bhash[i-1][j-1]]=(i>0)&&(j>0);
                A[top][bhash[i-1][j+1]]=(i>0)&&(j<9);
                A[top][bhash[i+1][j-1]]=(i<9)&&(j>0);
                A[top][bhash[i+1][j+1]]=(i<9)&&(j<9);
                ++top;
            }
}

bool eliminate(int row,int col)
{
    if(!A[row][col])
        for(int i=row+1,k;i<top;++i)
            if(A[i][col])
            {
                k=A[i][col];
                for(int j=0;j<blank.top;++j) A[row][j]-=A[i][j]/k;
                B[row]-=B[i]/k;
            }
    if(!A[row][col]) return 0;
    for(int i=0;i<row+1;++i)
    {
        for(int j=col;j<blank.top;++j) A[i][j]-=A[row][j]/A[i][col];
    }
}

void Gauss()
{
    for(int i=0;i<top;++i) //处理第i行
        for(int j=i;j<top;++j)
            if(eliminate(i,j)) break;
    
}

int main()
{
    for(int T,_=scanf("%d",&T);T--;)
    {
        scanf("%d",&_);
        for(int i=0;i<10;++i)
            for(int j=0;j<10;++j)
            {
                scanf("%d",&matrix[i][j]);
                if(matrix[i][j]==-1)
                {
                    bhash[i][j]=blank.top;
                    blank.add(Pii(i,j));
                }
            }
        generate();
        Gauss();
        printf("%d\n",_);
        for(int i=0;i<10;++i)
            for(int j=0;j<10;++j)
                printf("%d ",matrix);
    }
    return 0;
}