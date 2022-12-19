#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string.h>
#pragma once
#ifdef _DLL_EXPORTS
#define DLL_ _declspec(dllexport)
#else
#define DLL_ _declspec(dllimport)
#endif
#define DLogger_WARN 0x0
#define DLogger_ERROR 0x1
#define DLogger_INFO 0x2
#define DLogger_UNKNOW 0x3
/*设置日志文件*/
DLL_ void SetLogFile(char* FileName);
/*获取日志文件位置*/
DLL_ void GetLogFilePath(char* out);
/*输出一行带属性文本*/
DLL_ void WriteLine(char* Text, WORD Attributes);
/*日志记录*/
DLL_ void Log(char Text[], int level);
/*输出带属性文本*/
DLL_ void Write(wchar_t* Text, WORD Attributes);
/*输出带属性文本*/
DLL_ void Write(char* Text, WORD Attributes);