#pragma once
#include "pch.h"
#include <Windows.h>
EXTERN_C void utf8ToGbk(char* utf8String, char* gbkString);
EXTERN_C void Char2Wchar(wchar_t* wcharStr, const char* charStr);