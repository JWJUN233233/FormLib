#include <Windows.h>
#include "Logger.h"
#include <fstream>
#pragma once
#define _DLL_EXPORTS
#ifdef _DLL_EXPORTS
#define DLL _declspec(dllexport)
#else
#define DLL _declspec(dllimport)
#endif
#pragma warning(disable : 4996)
#define itoa(_Value, _Buffer)    _ltoa(_Value, _Buffer, 10)

// dllmain.cpp : 定义 DLL 应用程序的入口点。
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    char buffer[32];
    std::string _buffer = "";
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        __time64_t rawtime;
        struct tm info;
        time(&rawtime);
        _localtime64_s(&info, &rawtime);
        itoa(info.tm_year + 1900, buffer);
        _buffer += buffer;
        _buffer += "-";
        itoa(info.tm_mon + 1, buffer);
        _buffer += buffer;
        _buffer += "-";
        itoa(info.tm_mday, buffer);
        _buffer += buffer;
        _buffer += ".log";
        SetLogFile((char*)_buffer.c_str());
        Log((char*)"DLogger.dll Loaded");
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        Log((char*)"DLogger.dll Unloaded");
        logfile.close();
        break;
    }
    return TRUE;
}

