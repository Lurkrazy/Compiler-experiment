#include<stdio.h>
#include<ctype.h>
#include<string.h>


char Scanin[300],Scanout[300];
FILE *fin,*fout;

int es;
char sym;
char error[2];
int j,k;

char token[50];

int E();
int EX();
int T();
int TX();
int F();

int F()
{
  if (token[j]=='i')  j=j+1;
  else
  {
    if (token[j]=='(')
	{
	  j=j+1;
      es=E();
	  if (es>0) return(es);
	  if (token[j]==')') j=j+1;
      else es=1;
	}
	else
	  if (token[j]=='\n') es=0;
	  else {es=2; error[0]=token[j];error[1]='\0';}
  }
  return(es);	  
}

int EX()
{
  if (token[j]=='+') 
  {
      j=j+1;
	  es=T();
	  if (es>0) return(es);
	  es=EX();
  }
  return(es);
}

int E()
{
   es=T();
   if (es>0) return(es);
   es=EX();
   return(es);
}

int T()
{
   es=F();
   if (es>0) return(es);
   es=TX();
   return(es);
}

int TX()
{
  if (token[j]=='*') 
  {
      j=j+1;
	  es=F();
	  if (es>0) return(es);
	  es=TX();
  }
  return(es);
}




void main()              
{
	printf("请输入源程序文件名:");
	scanf("%s",Scanin);
	printf("请输入语法分析输出文件名:");
	scanf("%s",Scanout);
	if((fin=fopen(Scanin,"r"))==NULL)    
		printf("\n创建语法分析输入文件出错！\n");
	if((fout=fopen(Scanout,"w"))==NULL)    
		printf("\n创建语法分析输出文件出错！\n");
	
	fprintf(fout,"%s\t%s\t%s\n","算术表达式","是否合乎语法","非法原因");

	sym=getc(fin);
    j=0;
	
	while(sym!=EOF)
	{
		while (sym!='\n'||sym!=EOF)
		{
			while(sym==' '||sym=='\t') sym=getc(fin);
		    if (sym=='\n'||sym==EOF) break;
			token[j]=sym;
			j=j+1;
			sym=getc(fin);
        }
		token[j]='\0';
		k=j;
				
		j=0;
		
		es=0;
		es=E();

		printf("%s\n",token);
		if (es==0 && k==j) fprintf(fout,"%s\t\t%s\n",token,"合法");
		else 
		  if (es==1)
			fprintf(fout,"%s\t\t%s\t\t%s\n",token,"非法","缺少右括号");
		  else 
			if (es==2) 
			  fprintf(fout,"%s\t\t%s\t\t%s%s%d%s%s\n",token,"非法","非法字符--","第",j+1,"位字符：",error);
			else
			{ 
			  fprintf(fout,"%s\t\t%s\t\t%s",token,"非法","前面部分合法");
			  token[j]='\0';
			  fprintf(fout,"%s\n",token);
			}
		j=0;
		if (sym!=EOF) sym=getc(fin);
	}
}

