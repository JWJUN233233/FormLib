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
/*������־�ļ�*/
DLL void SetLogFile(char* FileName);
/*��ȡ��־�ļ�λ��*/
DLL void GetLogFilePath(char* out);
/*���һ�д������ı�*/
DLL void WriteLine(char* Text, WORD Attributes);
/*��־��¼*/
DLL void Log(char Text[], int level);
/*����������ı�*/
DLL void Write(wchar_t* Text, WORD Attributes);
/*����������ı�*/
DLL void Write(char* Text, WORD Attributes);