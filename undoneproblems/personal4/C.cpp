#include <bits/stdc++.h>

using namespace std;

const char word[30][6]={
    ".-",  //a
    "-...",
    "-.-.",
    "-..",
    ".", //e
    "..-.",
    "--.",
    "....",
    "..",  //i
    ".---",
    "-.-",
    ".-..",
    "--", //m
    "-.",
    "---",
    ".--.",
    "--.-", // q
    ".-.",
    "...",
    "-",
    "..-", //u
    "...-",
    ".--",
    "-..-",
    "-.--", //y
    "--.."
};

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    char str[6],clear[6];
    vector<char> v;
    while(1)
    {
        int state=scanf("%5[^/^ ^\n^\r]",str);
        if(state!=1) v.push_back(' ');
        else for(char i=0;i<26;++i)
        {
            if(!strcmp(str,word[(int)i]))
            {
                v.push_back(i+'A');
                break;
            }
        }
        state=scanf("%1[/]",clear);
        if(state!=1)
        {
            for(char c:v) printf("%c",c);
            puts("");
            scanf("%3[ \n\r]",clear);
            v=vector<char>();
        }
        if(state==-1)
        {
            break;
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-09 12:50:57	K
==================================================================*/