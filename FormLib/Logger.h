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
/*������־�ļ�*/
DLL_ void SetLogFile(char* FileName);
/*��ȡ��־�ļ�λ��*/
DLL_ void GetLogFilePath(char* out);
/*���һ�д������ı�*/
DLL_ void WriteLine(char* Text, WORD Attributes);
/*��־��¼*/
DLL_ void Log(char Text[], int level);
/*����������ı�*/
DLL_ void Write(wchar_t* Text, WORD Attributes);
/*����������ı�*/
DLL_ void Write(char* Text, WORD Attributes);