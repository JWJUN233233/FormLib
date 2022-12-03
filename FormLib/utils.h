#include <Windows.h>
#pragma once
void utf8ToGbk(char utf8String[], char gbkString[]);
int Char2Wchar(wchar_t* wcharStr, const char* charStr);
LPCWSTR toWchar_t(const char str[]);