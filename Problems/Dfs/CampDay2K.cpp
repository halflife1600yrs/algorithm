#include <bits/stdc++.h>

using namespace std;

char pos[15400][12];
int sticks[12],maxi,top;
bool ans[12],able[4];

void init()
{
    char tri[4][3];
    int h1,h2;
    bool used[12]={};
    tri[0][0]=top=0;
    for(int i=1;i<11;++i)
    { //第一个三角形第二条边
        used[i]=1,tri[0][1]=i;
        for(int j=i+1;j<12;++j)
        { //第一个三角形第三条边
            used[j]=1,tri[0][2]=j;
            for(int k=1;k<4;++k) //第二个三角形第一条边
                if(!used[k])
                {
                    h1=k;
                    used[k]=1,tri[1][0]=k;
                    break;
                }
            for(int k=h1+1;k<11;++k)
            { //第二个三角形第二条边，此时开始需要检验是否已用
                if(used[k]) continue;
                used[k]=1,tri[1][1]=k;
                for(int l=k+1;l<12;++l)
                { //第二个三角形第三条边
                    if(used[l]) continue;
                    used[l]=1,tri[1][2]=l;
                    for(int m=h1+1;m<7;++m) //第三个三角形第一条边
                        if(!used[m])
                        {
                            h2=m;
                            used[m]=1,tri[2][0]=m;
                            break;
                        }
                    for(int m=h2+1;m<11;++m)
                    { //第三个三角形第二条边
                        if(used[m]) continue;
                        used[m]=1,tri[2][1]=m;
                        for(int n=m+1;n<12;++n)
                        { //第三个三角形第三条边
                            if(used[n]) continue;
                            used[n]=1,tri[2][2]=n;
                            int p=0;
                            for(int o=h2+1;o<12;++o) //剩余的都放到第四个三角形
                                if(!used[o]) tri[3][p++]=o;
                            // printf("%d %d %d ",tri[0][0],tri[0][1],tri[0][2]);
                            // printf("%d %d %d ",tri[1][0],tri[1][1],tri[1][2]);
                            // printf("%d %d %d ",tri[2][0],tri[2][1],tri[2][2]);
                            // printf("%d %d %d\n",tri[3][0],tri[3][1],tri[3][2]);
                            pos[top][0]=tri[0][0],pos[top][1]=tri[0][1],pos[top][2]=tri[0][2];
                            pos[top][3]=tri[1][0],pos[top][4]=tri[1][1],pos[top][5]=tri[1][2];
                            pos[top][6]=tri[2][0],pos[top][7]=tri[2][1],pos[top][8]=tri[2][2];
                            pos[top][9]=tri[3][0],pos[top][10]=tri[3][1],pos[top][11]=tri[3][2];
                            ++top;
                            used[n]=0;
                        }
                        used[m]=0;
                    }
                    used[h2]=0;
                    used[l]=0;
                }
                used[k]=0;
            }
            used[h1]=0;
            used[j]=0;
        }
        used[i]=0;
    }
}

void check()
{
    int tmp;
    bool can[4];
    for(int i=0;i<15400;++i)
    {
        tmp=0;
        if(sticks[pos[i][0]]>sticks[pos[i][2]]-sticks[pos[i][1]]) ++tmp,can[0]=1;
        else can[0]=0;
        if(sticks[pos[i][3]]>sticks[pos[i][5]]-sticks[pos[i][4]]) ++tmp,can[1]=1;
        else can[1]=0;
        if(sticks[pos[i][6]]>sticks[pos[i][8]]-sticks[pos[i][7]]) ++tmp,can[2]=1;
        else can[2]=0;
        if(sticks[pos[i][9]]>sticks[pos[i][11]]-sticks[pos[i][10]]) ++tmp,can[3]=1;
        else can[3]=0;
        if(tmp>maxi)
        {
            maxi=tmp;
            memcpy(able,can,sizeof(able));
            memcpy(ans,pos[i],sizeof(ans));
        }
        if(maxi==4) return;
    }
}

int main()
{
    init();
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        for(int i=0;i<12;++i) scanf("%d",&sticks[i]);
        sort(sticks,sticks+12);
        maxi=0;
        check();
        printf("Case #%d: %d\n",_,maxi);
        if(maxi)
        {
            if(able[0]) printf("%d %d %d\n",sticks[ans[0]],sticks[ans[1]],sticks[ans[2]]);
            if(able[1]) printf("%d %d %d\n",sticks[ans[3]],sticks[ans[4]],sticks[ans[5]]);
            if(able[2]) printf("%d %d %d\n",sticks[ans[6]],sticks[ans[7]],sticks[ans[8]]);
            if(able[3]) printf("%d %d %d\n",sticks[ans[9]],sticks[ans[10]],sticks[ans[11]]);
        }
    }
    return 0;
}