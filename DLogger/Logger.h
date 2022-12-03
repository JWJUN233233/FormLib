#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <fstream>
#include <filesystem>
#include "utils.h"
#pragma once
#define _DLL_EXPORTS
#ifdef _DLL_EXPORTS
#define DLL _declspec(dllexport)
#else
#define DLL _declspec(dllimport)
#endif
#define DLogger_WARN 0x0
#define DLogger_ERROR 0x1
#define DLogger_INFO 0x2
#define DLogger_UNKNOW 0x3
#define DLogger_default 0x7
std::ofstream logfile;
std::string logpath;
using std::filesystem::current_path;
#pragma warning(disable : 4996)
/*设置日志文件*/
DLL void SetLogFile(char* FileName) {
	logfile.close();
	logfile.open(FileName);
	logpath = FileName;
}
/*获取日志文件位置*/
DLL void GetLogFilePath(char* out) {
	std::filesystem::path p = current_path();
	char buffer[512];
	Wchar2Char((wchar_t*)p.c_str(), buffer);
	std::string _buffer = buffer;
	_buffer += "\\";
	_buffer += logpath;
	char* tmp = (char*)_buffer.c_str();
	sprintf(out, "%s", tmp);
}
/*输出一行带属性文本*/
DLL void WriteLine(char* Text, WORD Attributes = DLogger_default) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	std::cout << Text << std::endl;
	logfile << Text << std::endl;
	SetConsoleTextAttribute(handle, colorOld);
};
/*日志记录*/
DLL void Log(char Text[], int level = DLogger_WARN) {
	__time64_t rawtime;
	struct tm info;
	time(&rawtime);
	_localtime64_s(&info, &rawtime);
	int threadId = GetCurrentThreadId();
	std::cout << "[" <<
		info.tm_hour <<
		":" <<
		info.tm_min <<
		":" << info.tm_sec <<
		"]" <<
		" [Thread-" <<
		threadId <<
		"/"
		;
	logfile << "[" <<
		info.tm_hour <<
		":" <<
		info.tm_min <<
		":" << info.tm_sec <<
		"]" <<
		" [Thread-" <<
		threadId <<
		"/"
		;
	switch (level) {
	case DLogger_INFO: {
		std::cout << "INFO]";
		logfile << "INFO]";
		WriteLine(Text, 7);
		break;
	}
	case DLogger_WARN: {
		std::cout << "WARN]";
		logfile << "WARN]";
		WriteLine(Text, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	}
	case DLogger_ERROR: {
		std::cout << "ERROR]";
		logfile << "ERROR]";
		WriteLine(Text, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	}
	case DLogger_UNKNOW: {
		std::cout << "UNKNOW]";
		logfile << "UNKNOW]";
		WriteLine(Text, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	}
	}
};
/*输出带属性文本*/
DLL void Write(wchar_t* Text, WORD Attributes = DLogger_default) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	std::cout << Text;
	logfile << Text;
	SetConsoleTextAttribute(handle, colorOld);
}
/*输出带属性文本*/
DLL void Write(char* Text, WORD Attributes = DLogger_default) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	std::cout << Text;
	logfile << Text;
	SetConsoleTextAttribute(handle, colorOld);
};