#include<bits/stdc++.h>

using namespace std;

#define lld long long

lld a[6010];
int b[4];

int main() {
    int n,mark=1;
    scanf("%d",&n);
    while(n--){
        memset(a,0,sizeof(a));
        int len;
        lld max1=0,pos1,pos2;
        scanf("%d",&len);
        if(len>=4) {
            for (int i = 0; i < len; i++) {
                scanf("%lld", &a[i]);
            }
            for(int i=0;i<4;i++){
                for(int j=i+1;j<4;j++){
                    memset(b,0,sizeof(b));
                    if(a[i]*10+a[j]>max1) {
                        max1=a[i]*10+a[j];
                        b[i]=1;b[j]=1;
                        int k;
                        for(k=0;k<4;k++){
                            if(!b[k]) {pos1=k;break;}
                        }
                        for(k=k+1;k<4;k++){
                            if(!b[k]) {pos2=k;break;}
                        }
                    }
                }
            }
            // cout<<123<<' ';
            // cout<<max1<<' '<<pos1<<' '<<pos2<<endl;
            // cout<<456;
            string ans;
            for (int i = 0; i < len; i++) {
                if (i == pos1 || i == pos2) continue;
                lld tmp = a[i];
                string tstr;
                while (tmp) {
                    char ch = tmp % 10 + '0';
                    tstr = ch + tstr;
                    tmp /= 10;
                }
                ans += tstr;
            }
            cout << "Case #"<<mark++<<": "<<ans << '\n';
        }else {
            for(int i=0;i<3;i++) scanf("%lld",&a[i]);
            lld ans;
            ans=max(a[0],a[1]);
            ans=max(ans,a[2]);
            cout << "Case #"<<mark++<<": "<< ans << '\n';
        }
    }
    system("pause");
    return 0;
}
