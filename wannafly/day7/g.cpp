#include<bits/stdc++.h>

using namespace std;
#define lld long long

set<int> se[101];
vector<int> ve;

int main(){
    int n,m,tmp,num;
    scanf("%d%d",&n,&m);
    for(int i=0;i<101;i++) se[i].clear();

    for(int i=0;i<m;i++){
        scanf("%d",&num);
        for(int j=0;j<num;j++){
            scanf("%d",&tmp);
            ve.push_back(tmp);
        }
        for(int k=1;k<num;k++){
            for(int j=0;j<k;j++){
                se[ve[k]].insert(ve[j]);
                se[ve[k]].insert(se[ve[j]].begin(),se[ve[j]].end());
            }
        }
        ve.clear();
    }
    int ans=999999,sz;
    for(int i=1;i<=n;i++){
        if(se[i].find(i)!=se[i].end()) sz=se[i].size()-1;
        else sz=se[i].size();
        cout<<i<<" :"<<sz<<endl;
        ans=min(sz,ans);
    }
    printf("%d\n",ans+1);
    return 0;
}
