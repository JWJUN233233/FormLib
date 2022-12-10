#pragma once
#include <tchar.h>
#ifdef UNICODE
#define achar wchar_t
#define cachar  const wchar_t
#else
#define achar  char
#define cachar  const char
#endif