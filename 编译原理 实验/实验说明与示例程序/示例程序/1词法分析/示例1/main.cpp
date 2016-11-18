#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
/**
---关键字---
9
main   1
return 2
int    3
char   4
float  5
double 6
for    7
scan   8
print  9
---标识符---
10
----常整数----
11
----常实数--
12
----分界符--
8
{  20
}  21
(  22
)  23
;  24
,  25

----运算符---
7
+  10
-  11
*  12
/  13
<  14
>  15
=  16

*/
map<string,int>encode;//关键字、分界符、运算符
FILE *fp;
void ReadEncode()
{
    fp=fopen("encode.txt","r");
    if(fp==NULL)
    {
        printf("文件不能正常打开!\n");
        exit(0);
    }
    int n;
    fscanf(fp,"%d",&n);
    char  s[20];
    int value;
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
    fscanf(fp,"%d",&n);
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
    fscanf(fp,"%d",&n);
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
}

void solve()
{
    char ch;
    fp=fopen("code.c","r");
    if(fp==NULL)
    {
        printf("文件不能正常打开!\n");
        exit(0);
    }
    ch=fgetc(fp);
    string s;
    while(!feof(fp))
    {
        //1.识别分界符
        if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==';'||ch==',')
        {
            s=ch;
            printf("<%d,%c>\n",encode[s],ch);
            ch=fgetc(fp);
        }//2.运算符
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='>'||ch=='<'||ch=='=')
        {
            s=ch;
            printf("<%d,%c>\n",encode[s],ch);
            ch=fgetc(fp);
        }
        //(3).判断关键字和变量
        else if(isalpha(ch))
        {
            s="";
            //标识符以字母开头，后面跟数字或字母
            while(isalpha(ch)||isdigit(ch))
            {
                s+=ch;
                ch=fgetc(fp);
            }
            if(encode.find(s)!=encode.end())//关键字
            {
                printf("<%d,%s>\n",encode[s],s.c_str());
            }
            else//变量
                printf("<10,%s>\n",s.c_str());
        }//4.常数
        else if(isdigit(ch))
        {
            s="";
            int flag=0;
            while(isdigit(ch)||ch=='.')
            {
                if(ch=='.')flag=1;
                s+=ch;
                ch=fgetc(fp);
            }
            if(flag==0)//常整数
                printf("<11,%s>\n",s.c_str());
            else  //常实数
                printf("<12,%s>\n",s.c_str());
        }
        else
            ch=fgetc(fp);
    }
}
int main()
{
    freopen("output.txt","w",stdout);
    // 读取编码列表
    encode.clear();
    ReadEncode();
    solve();
    return 0;
}
