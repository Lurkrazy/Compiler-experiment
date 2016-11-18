#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main()
{
string sheet[5][6]={{"TA","TA","","","",""}, //预测分析表
{"","","e","+TA","","e"}, //行:E,A(代表 E1),T,B(代表 T1),F
{"FB","FB","","","",""}, //列:i,(,),+,*,$
{"","","e","e","*FB","e"}, //e代表空串
{"i","(E)","","","",""}};
vector<char> S;
vector<char> Stc;
vector<char> SOS;
string STC;
int YourChoice;
do{
cout<<endl;
S=SOS; //S代表分析栈,每次执行用空的SOS初始化
S.push_back('$');
S.push_back('E');
STC=""; //STC代表用户的表达式
cout<<"请输入您要分析的字符串:";
cin>>STC;
STC.resize(STC.size()+1);
STC[STC.size()-1]='$';
Stc=SOS; //Stc是将STC+$倒序压入的用户输入栈
for(int x=STC.size()-1;x>=0;--x)
Stc.push_back(STC[x]);
string YY="EATBF";
string XX="i()+*$";
while(!(S[S.size()-1]=='$'&&Stc[Stc.size()-1]=='$'))
{
int i=0,j=0;
////////////////////查表找到相应规则////////////////////
for(i=0;i<5;++i)
if(YY[i]==S[S.size()-1])
break;
for(j=0;j<6;++j)
if(XX[j]==Stc[Stc.size()-1])
break;
if(i>=5||j>=6) //如果查找超出表
{
cout<<"出错啦!"<<endl;
break;
}
else if(sheet[i][j]=="") //如果查到的为空规则
{
cout<<"出错啦!"<<endl;
break;
}
else
{
///////////////分析栈里的压栈与弹栈////////////////////
S.pop_back();
for(int k=sheet[i][j].size()-1;k>=0;--k)
S.push_back(sheet[i][j][k]);
if(S[S.size()-1]==Stc[Stc.size()-1]) //一般规则
{
S.pop_back();
Stc.pop_back();
}
else if(S[S.size()-1]=='e') //含空串的规则
{
S.pop_back();
if(S[S.size()-1]!='$'&&Stc[Stc.size()-1]!='$'&&S[S.size()-1]==Stc[Stc.size()-1])
{
S.pop_back();
Stc.pop_back();
}
}
}
}

if(S[S.size()-1]=='$'&&Stc[Stc.size()-1]=='$')
cout<<"分析成功!"<<endl;
cout<<"输入0继续,其它退出";
}while(cin>>YourChoice&&YourChoice==0);

return 0;
}
