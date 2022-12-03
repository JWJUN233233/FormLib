#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string.h>
#pragma once
#ifdef _DLL_EXPORTS
#define DLL _declspec(dllexport)
#else
#define DLL _declspec(dllimport)
#endif
#define DLogger_WARN 0x0
#define DLogger_ERROR 0x1
#define DLogger_INFO 0x2
#define DLogger_UNKNOW 0x3
/*设置日志文件*/
DLL void SetLogFile(char* FileName);
/*获取日志文件位置*/
DLL void GetLogFilePath(char* out);
/*输出一行带属性文本*/
DLL void WriteLine(char* Text, WORD Attributes);
/*日志记录*/
DLL void Log(char Text[], int level);
/*输出带属性文本*/
DLL void Write(wchar_t* Text, WORD Attributes);
/*输出带属性文本*/
DLL void Write(char* Text, WORD Attributes);