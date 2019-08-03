#include <bits/stdc++.h>
  
using namespace std;
  
const int MAXN=1e5+5,MAXV=MAXN*2,MAXE=MAXV*2;
  
int kind[MAXN],v;
vector<char> ans;
  
namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];
  
    int top, head[MAXV];
  
    void init() { top = 0, memset(head, -1, sizeof(head)); }
  
    int in[MAXV];
  
    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        ++in[to];
        head[fr] = top++;
    }
  
    void topsort()
    {
        queue<int> q;
        for(int i = 1; i <= v; ++i)
            if(!in[i]) q.push(i);
        ans.resize(0);
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            ans.push_back(kind[fr]);
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(!(--in[to])) q.push(to);
            }
        }
    }
}
  
char str[MAXN],c[MAXN];
vector<int> word[30];
int cnt[30];
 
inline int hsh(char x)
{
    return abs(x-'a');
}
 
int main()
{
    int n,m,l;
    scanf("%d %d",&n,&m);
    if(n==1)
    {
        printf("-1");
        return 0;
    }
    memset(cnt,-1,sizeof(cnt));
    v=1;
    G::init();
    for(int q=0;q<m*(m-1)/2;++q)
    {
        scanf("%s %d",c,&l);
        if(l) scanf("%s",str);
        else str[0]=0;
        int n[2]={0,0},m[2];
        m[0]=hsh(c[0]),m[1]=hsh(c[1]);
        if(cnt[m[0]]==-1) word[m[0]].resize(0);
        if(cnt[m[1]]==-1) word[m[1]].resize(0);
        for(int i=0;i<l;++i)
        {
            if(str[i]==c[0])
            {
                if(cnt[m[0]]==-1)
                    kind[v]=c[0],word[m[0]].push_back(v++);
                if(i&&n[1]&&str[i-1]==c[1])
                    G::add(word[m[1]][n[1]-1],word[m[0]][n[0]]);
                ++n[0];
            }
            if(str[i]==c[1])
            {
                if(cnt[m[1]]==-1)
                    kind[v]=c[1],word[m[1]].push_back(v++);
                if(i&&n[0]&&str[i-1]==c[0])
                    G::add(word[m[0]][n[0]-1],word[m[1]][n[1]]);
                ++n[1];
            }
        }
        if(cnt[m[0]]==-1)
        {
            for(int i=1;i<word[m[0]].size();++i) G::add(word[m[0]][i-1],word[m[0]][i]);
            cnt[m[0]]=n[0];
        }
        else if(cnt[m[0]]!=n[0])
        {
            printf("-1\n");
            return  0;
        }
        if(cnt[m[1]]==-1)
        {
            for(int i=1;i<word[m[1]].size();++i) G::add(word[m[1]][i-1],word[m[1]][i]);
            cnt[m[1]]=n[1];
        }
        else if(cnt[m[1]]!=n[1])
        {
            printf("-1\n");
            return  0;
        }
    }
    --v;
    G::topsort();
    if(ans.size()!=n) printf("-1\n");
    else
    {
        for(auto cc:ans) printf("%c",cc); printf("\n");
    }
    return 0;
}
 
/*==================================================================
added at 2019-08-02 17:13:08 NK885h
1 1
拓扑排序的题目,思路蛮有趣的
读入字符串时特判长度为0
==================================================================*/