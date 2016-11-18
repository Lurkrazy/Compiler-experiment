
#include "getsym.h"
//关键字
const char* const keytxt[MAX_KEYWORD]=
{
	"of","array","program","mod","and","or",
	"not","begin","end","if","then","else","while",
	"do","call","const","type","var",
	"procedure"
};
//单字运算符
const char opatxt[MAX_OPWORDA]=
{
	'+','-','*','/','=','#','<','>'
};
//双字运算符
const char* const opbtxt[MAX_OPWORDB]=
{
	"<=",">=",":=","<>"
};
//单字界符
const char eoptxt[MAX_ENDWORD]=
{
	'(',')',',',';','.','[',']',':'
};
//错误提示信息
const char* const errtxt[MAX_ERROR]=
{
	"OK",	//Not used.
	"Too long symbol",
	"Too long number",
	"Mixed number and letter",
	"Unkown operator",
};

int getsym(const char *in,struct SYM *out,int *ln,struct FORM *form)
{
	char b[MAX_BUFFER];			//建符号缓冲区
	int i,m=0,n=0,e=0;			//序号/非字符数/字符数/出错标记
	memset(out,0,sizeof(struct SYM));
	while(!ISCHAR(*in))			//滤出前面的非字符
	{
		if(*in==10) (*ln)++;//换行时,ln++
		if(*in++) m++; else return 0;	//如果无字符则退出
	}
	out->line=*ln;
	if(ISLETTER(*in))			//字母开头情况
	{
		while(ISLETTER(*in)||ISNUMBER(*in))
		{
			if(n<=MAX_SYMLEN) b[n]=*in;
			n++; in++;
		}
		b[MAX_SYMLEN]=0;		//符号结尾置0
		if(n<MAX_SYMLEN) b[n]=0;
		strcpy(out->name,b);
		if(n>MAX_SYMLEN)		//超出符号最大长度
		{
			out->type=TYPE_ERROR;
			out->id=ERR_OVERSYMLEN;
		}
		else
		{
			for(i=0;i<MAX_KEYWORD;i++)
				if(strcmp(b,keytxt[i])==0) break;
			if(i<MAX_KEYWORD)	//属于关键字
			{
				out->type=TYPE_KEYWORD;
				out->id=i;
			}
			else				//不属于关键字
			{
				for(i=0;i<form->symnum;i++)
					if(strcmp(b,form->symf[i].name)==0) break;
				if(i==form->symnum)	//不在符号表中则添加
				{
					if(form->symnum>=MAX_SYMFORM)
					{			//超出符号表范围产生严重错误
						out->type=TYPE_ERROR;
						out->id=ERR_OVERSYMFORM;
						return m+n;
					}
					form->symf[i].id=i;
					strcpy(form->symf[i].name,b);
					form->symnum++;
				}
				out->type=TYPE_SYMBOL;	//符号类型
				out->id=i;
			}
		}
		return m+n;
	}
	if(ISNUMBER(*in))			//数字开头情况
	{
		e=0;
		while(ISNUMBER(*in)||ISLETTER(*in))
		{
			if(ISLETTER(*in)) e=1;	//含字母则置出错标记
			if(n<=MAX_NUMLEN) b[n]=*in;
			n++; in++;
		}
		b[MAX_NUMLEN]=0;		//数字尾置0
		if(n<MAX_NUMLEN) b[n]=0;
		strcpy(out->name,b);
		if(e||n>MAX_NUMLEN)	//有出错标记或超出数字最大长度
		{
			out->type=TYPE_ERROR;
			if(e)				//含字母情况
				out->id=ERR_NUMBER;
			else				//超出数字最大长度情况
				out->id=ERR_OVERNUMLEN;
		}
		else					//无错情况
		{
			if(form->numnum>=MAX_NUMFORM)
			{					//超出常量表范围产生严重错误
				out->type=TYPE_ERROR;
				out->id=ERR_OVERNUMFORM;
				return m+n;
			}
			form->numf[form->numnum].id=form->numnum;
			strcpy(form->numf[form->numnum].name,b);
			out->type=TYPE_NUMBER;
			out->id=form->numnum;
			form->numnum++;
		}
		return m+n;
	}
	for(i=0;i<MAX_OPWORDB;i++)	//双字运算符情况
		if(*(short*)in==*(short*)(opbtxt[i])) break;
	if(i<MAX_OPWORDB)
	{
		out->type=TYPE_OPWORD;
		out->id=MAX_OPWORDA+i;
		*(short*)out->name=*(short*)opbtxt[i];
		out->name[2]=0;
		return m+2;
	}
	out->name[0]=*in;
	out->name[1]=0;
	for(i=0;i<MAX_OPWORDA;i++)	//单字运算符情况
		if(*in==opatxt[i]) break;
	if(i<MAX_OPWORDA)
	{
		out->type=TYPE_OPWORD;
		out->id=i;
		return m+1;
	}
	for(i=0;i<MAX_ENDWORD;i++)	//单字界符情况
		if(*in==eoptxt[i]) break;
	if(i<MAX_ENDWORD)
	{
		out->type=TYPE_ENDWORD;
		out->id=i;
		return m+1;
	}
	out->type=TYPE_ERROR;
	out->id=ERR_WRONGOP;		//其他符号则出错
	return m+1;
}

int getsyminfo(const char *in,struct SYMINFO *out)
{
	int offset,ln=1;			//每次取词偏移量/当前行数
	memset(out,0,sizeof(struct SYMINFO));
	while(1)
	{
		offset=getsym(in,&out->sym[out->num],&ln,&out->form);
		if(offset==0) break;	//完成取词则退出
		if(out->num>=MAX_SYM) return ERR_OVERSYMNUM;//超出符号信息最大值
		if(out->sym[out->num].type==TYPE_ERROR&&out->sym[out->num].id>=10000)
			return out->sym[out->num].id;//有严重错误则退出
		out->num++;
		in+=offset;
	}
	return 0;
}
