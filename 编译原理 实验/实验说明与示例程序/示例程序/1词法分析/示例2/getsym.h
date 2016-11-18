
#ifndef _GETSYM_H_
#define _GETSYM_H_

#include <stdlib.h>		//For memset()
#include <string.h>		//For strcpy()

#define ISLETTER(c)	((c)>='A'&&(c)<='Z'||(c)>='a'&&(c)<='z')
#define ISNUMBER(c)	((c)>='0'&&(c)<='9')
#define ISCHAR(c)	((c)>=33 &&(c)<=126)

#define MAX_SYM			32768	//最大符号量
#define MAX_SYMFORM		1024	//最大符号表长度
#define	MAX_NUMFORM		4096	//最大常数表长度

#define MAX_SYMLEN		31		//最大符号长度
#define MAX_NUMLEN		10		//最大常数长度
#define MAX_BUFFER		MAX_SYMLEN+1//最大缓冲长度

#define MAX_KEYWORD		19		//关键字数量
#define MAX_OPWORDA		8		//单字运算符数量
#define MAX_OPWORDB		4		//双字运算符数量
#define MAX_ENDWORD		8		//单字界符数量
#define MAX_ERROR		5		//错误类型数量

#define TYPE_KEYWORD	1		//关键字类型号
#define TYPE_SYMBOL		2		//符号类型号
#define TYPE_NUMBER		3		//常量类型号
#define TYPE_OPWORD		4		//运算符类型号
#define TYPE_ENDWORD	5		//界符类型号
#define TYPE_ERROR		-1		//错误类型号

#define ERR_OVERSYMLEN	1		//以下是一般错误号
#define ERR_OVERNUMLEN	2
#define ERR_NUMBER		3
#define ERR_WRONGOP		4
#define ERR_OVERSYMFORM	10001	//以下是严重错误号
#define ERR_OVERNUMFORM 10002
#define ERR_OVERSYMNUM	10003
#define ERR_OVERERRNUM	10004

#ifdef __cplusplus
extern "C" {
#endif

struct SYM		//符号描述结构体(含错误描述结构)
{
	int type;		//类型号(0:错误)
	int id;			//ID号(错误值)
	int line;		//所在行数

	char name[MAX_SYMLEN+1];	//所取的词
};

struct FORM		//表格结构体
{
	int symnum;
	int numnum;
	struct SYMF		//符号表项结构体
	{
		int id;
		char name[MAX_SYMLEN+1];
	}symf[MAX_SYMFORM];
	struct NUMF		//常量表项结构体
	{
		int id;
		char name[MAX_NUMLEN+1];
	}numf[MAX_NUMFORM];
};

struct SYMINFO	//词法分析信息结构体
{
	int num;
	struct SYM sym[MAX_SYM];
	struct FORM form;
};
//取词函数
int __stdcall getsym(const char *in,struct SYM *out,int *ln,struct FORM *form);
//取所有词函数
int __stdcall getsyminfo(const char *in,struct SYMINFO *out);

#ifdef  __cplusplus
}
#endif
#endif
