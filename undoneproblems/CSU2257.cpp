#include <bits/stdc++.h>

using namespace std;

int test(int x)
{
    for(int i=0;i<44800;++i)
        if(1ll*i*(i-1)/2==x) return i;
    return -1;
}

bool check(int num_0,int o_l,int l_o,int num_1)
{
    if(num_0<0||num_1<0)
        return 0;
    if(o_l+l_o!=num_0*num_1)
        return 0;
    return 1;
}

void generate(int num_0,int o_l,int l_o,int num_1)
{
    
}

int main()
{
    int o_o,o_l,l_o,l_l;
    scanf("%d%d%d%d",&o_o,&o_l,&l_o,&l_l);
    vector<int> v1,v2;
    int num_0=test(o_o),num_1=test(l_l);
    v1.push_back(num_0),v2.push_back(num_1);
    if(!num_0) v1.push_back(1);
    if(!num_1) v2.push_back(0);
    for(vector<int>::iterator it=v1.begin();it!=v1.end();it++)
    {
        for(vector<int>::iterator it=v2.begin();it!=v2.end();it++)
        {
            if(check(num_0,o_l,l_o,num_1)) break;
            generate(num_0,o_l,l_o,num_1);
            return 0;
        }
    }
    printf("impossible\n");
    return 0;
}