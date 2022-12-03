// LoggerMain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "IColorfulOut.h"
#include "Logger.h"
#pragma comment(lib,"DLogger.lib")
#pragma once
int main()
{
    char text[] = "hello";
    Log(text, DLogger_WARN);
    Log(text, DLogger_UNKNOW);
    Log(text, DLogger_ERROR);
    Log(text, DLogger_INFO);
    RedOut << "1\n" << "2" << endl << 123 << endl << 12.412322 << endl;
    char tmp[512];
    GetLogFilePath(tmp);
    Log(tmp, DLogger_ERROR);
}