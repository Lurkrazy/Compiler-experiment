#include <iostream>
#include <Stack>                  //引入栈文件
#include <string>
using namespace std;

char j[128];
int M[5][6]={{0,0,1,0,1,0},{2,0,0,3,0,3},{0,0,4,0,5,0},{0,0,6,0,6,0},{8,7,0,8,0,8}}; //预测分析表
				

void error()                       //出错函数
{
	cout<<"error !"<<endl;
	exit(0);
}

void main()
{
	cout<<"输入表达式："<<endl;
	cin>>j;

	stack<char> A;                  //分析栈
	stack<char> B;                  //存放输入串的栈
	int m=0;         
	for(int ss=0;j[ss]!='\0';ss++)  //求输入串的长度
	{
		m++;
	}
	for(int w=m-1;w>=0;w--)
	{
		B.push(j[w]);               //将输入串逆向压入栈中
	}
	A.push('$');
	A.push('E');

	for(int k=0;;k++)
	{
		char x=A.top();
		A.pop();
		if(x=='+'||x=='*'||x=='('||x==')'||x=='i')
		{
			if(x==B.top())
				B.pop();
			else
			{
				cout<<"123";
				error();
			}
			
		}
		else if(x=='E'||x=='e'||x=='F'||x=='T'||x=='t'||x=='$')
		{
			if(x=='$')
			{
				if(B.top()=='$')
				{
					cout<<"succee !"<<endl;
					exit(0);
				}	
				else
				{	
					error();
					exit(0);
				}
			}
			else
			{
				int h;
				switch(x)
				{
				case 'E':
					h=0;break;
				case 'e':
					h=1;break;
				case 'F':
					h=2;break;
				case 'T':
					h=3;break;
				case 't':
					h=4;break;
				}

				int h2;
				switch(B.top())
				{
				case '+':
					h2=0;break;
				case '*':
					h2=1;break;
				case '(':
					h2=2;break;
				case ')':
					h2=3;break;
				case 'i':
					h2=4;break;
				case '$':
					h2=5;break;
				}
				
				int w2=M[h][h2];
				switch(w2)
				{
				case 0:
					error();
					break;
				case 1:
					{
						A.push('e');
						A.push('T');
						break;
					}
				case 2:
					{
						A.push('e');
						A.push('T');
						A.push('+');
						break;
					}
				case 3:
						;
						break;
				case 4:
					{
						A.push(')');
						A.push('E');
						A.push('(');
						break;
					}
				case 5:
						A.push('i');
						break;
				case 6:
					{
						A.push('t');
						A.push('F');
						break;
					}
				case 7:
					{
						A.push('t');
						A.push('F');
						A.push('*');
						break;
					}
				case 8:
					{
						;
						break;
					}
				}					  
			}
		}
	}
}
