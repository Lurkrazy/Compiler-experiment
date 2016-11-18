
#pragma once
#pragma comment(linker, "/OPT:NOWIN98")
#pragma comment(linker, "/SECTION:.DWING,")
#pragma comment(linker, "/MERGE:.text=.DWING")
#pragma comment(linker, "/MERGE:.rdata=.DWING")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>	//For All
#include <commdlg.h>	//For OPEN&SAVEFILE Dialog
#include <stdio.h>		//For Operate File
#include "resource.h"	//For Main Dialog & Menu

extern "C" char* errtxt[];
extern "C" char* keytxt[];
extern "C" char  opatxt[];
extern "C" char* opbtxt[];
extern "C" char  eoptxt[];
//对话框消息处理函数
BOOL CALLBACK dlgproc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam);
