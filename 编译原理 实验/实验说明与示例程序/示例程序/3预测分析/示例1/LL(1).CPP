#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char stack[80];
int i=0;
void main()
{
	char string[20],str[10];
	int j=0,k,l,m,n,ii,count=1;
	char *table[7][7]={
	{"DB","DB","","","","",""},
	{"","","e","CDB","CDB","","e"},
	{"","","","+","-","",""},
	{"GE","GE","","","","",""},
	{"","","e","e","e","FGE","e"},
	{"","","","","","*",""},
	{"(A)","i","","","","",""} //定义LL(1)分析表
	};
	printf("Input express:");
	scanf("%s",string);
	stack[i]='$';    //栈底压入$
	i++;
	stack[i]='A';    //压入开始符
	printf("%-5s%-15s%-15s\n","step","stack","string");
	while(string[j]!='\0')
	{
		printf("%-5d",count++);
		for(ii=0;ii<=i;ii++)
			printf("%c",stack[ii]);
		for(;ii<15;ii++)
			printf(" ");
		for(ii=j;string[ii]!='\0';ii++)
			printf("%c",string[ii]);
		printf("\n");
		if(stack[i]=='$' && string[j]=='$')
		{
			printf("Success!\n");
			exit(0);
		}
		if(stack[i]<'A' || stack[i]>'Z')
		{
			if(stack[i]==string[j])
			{
			    i--;
			    j++;
			}
			else
			{
				printf("\7Error!\n");
				exit(1);
			}
		}
        else
		{
			k=stack[i]-65;
			switch(string[j])
			{
			case '(': l=0; break;
			case 'i': l=1; break;
			case ')': l=2; break;
			case '+': l=3; break;
			case '-': l=4; break;
			case '*': l=5; break;
			case '$': l=6; break;
			}
			m=strlen(table[k][l]);
			if(m==0)
			{
				printf("\7Error\n");
				exit(1);
			}
			else if(strcmp(table[k][l],"e")==0)
			{
				i--;
			}
			else
			{
				strcpy(str,table[k][l]);
				i--;
				for(n=m-1;n>=0;n--)
				{
					i++;
					stack[i]=str[n];
				}
			}
		}
	}
}

		


		







