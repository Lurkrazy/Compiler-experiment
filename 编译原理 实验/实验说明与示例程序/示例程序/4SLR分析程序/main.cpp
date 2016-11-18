#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include <map>
using namespace std;

void show();
//文法G[E]的SLR(1)分析表之ACTION
string action[16][8]=
{   {"S5","","","","","S4","",""},
    {"","S6","S7","","","","","acc"},
    {"","r3","r3","S8","S9","","r3","r3"},
    {"","r6","r6","r6","r6","","r6","r6"},
    {"S5","","","","","S4","",""},
    {"","r8","r8","r8","r8","","r8","r8"},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"","S6","S7","","","","S15",""},
    {"","r1","r1","S8","S9","","r1","r1"},
    {"","r2","r2","S8","S9","","r2","r2"},
    {"","r4","r4","r4","r4","","r4","r4"},
    {"","r5","r5","r5","r5","","r5","r5"},
    {"","r7","r7","r7","r7","","r7","r7"},
};
//文法G[E]的SLR(1)分析表之GOTO
int GOTO[16][3]=
{   {1,2,3},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {10,2,3},
    {0,0,0},
    {0,11,3},
    {0,12,3},
    {0,0,13},
    {0,0,14}
};
char str[100];//产生式
string redu[9]= {"E->E+T", "E->E-T", "E->T","T->T*F", "T->T/F", "T->F","F->(E)","F->i"};
map<char,int>id;
void init()
{  //编码将终结符和非终结符分别编码
    char s[]="i+-*/()$";
    for(int i=0;i<8;i++) id[s[i]]=i;
    id['E']=0;id['T']=1;id['F']=2;
}
int solve()
{
    stack<int> state;
    stack<char> sign;
    state.push(0); //状态栈压入0
    sign.push('$');//符号栈顶压入'$'
    char a;
    int j=0,len;
    len=strlen(str);
    str[len]='$';//输入串的尾部添加'$'
    do{
        while(str[j]==' ')j++;//去除表达式中的空格
        a=str[j];//取输入串的首字母
        if(id.find(a)==id.end())return 1;//非法，表达式中存在非法字符
        string temp=action[state.top()][id[a]];
        if(temp.length()>0)//对应的ACTION不为空
        {
            //printf("%s  %d  %c\n",temp.c_str(),state.top(),sign.top());
            if(temp=="acc")return 0;//合法
            if(temp[0]=='S')//移进
            {
                j++;sign.push(a);
                int index=temp[1]-'0';
                if(index==1)index=15;
                state.push(index);//压入新的状态
            }
            else//归约
            {
                int index=temp[1]-'1';//这是第几个产生式
                //状态栈删除L个状态 和符号栈L个符号
                for(int l=redu[index].length();l>3;l--)
                {   state.pop();
                    sign.pop();
                }
                sign.push(redu[index][0]);//压入产生式左边的
                int tt=GOTO[state.top()][id[sign.top()]];
                state.push(tt);//状态栈压入新的状态
            }
        }
        else
            return 2;//非法,对应的ACTION为空
    }while(a!='$'||sign.top()!='$'); //只要有一个没空
}
int main()
{
   // show();
    init();
    freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
    while(gets(str))
    {
        printf("%-20s",str);
        int flag=solve();
        if(flag==0)printf(" 合法！\n");
        else  printf("不合法！\n");
    }
    return 0;
}
/*
void show()
{
    char s[]=" i+-x/()$ETF";
    for(int i=0;i<=11;i++)
        printf("%-5c",s[i]);
        printf("\n");
    for(int i=0;i<=15;i++)
    {
        printf("%-5d",i);
        for(int j=0;j<8;j++)
        {
            if(action[i][j].length()>0)
               printf("%-5s",action[i][j].c_str());
            else
                printf("%-5s","-");
        }
        for(int j=0;j<3;j++)
            printf("%-5d",GOTO[i][j]);
        printf("\n");
    }

}*/
