#pragma once
#include <Windows.h>
#include "pch.h"
namespace FormLib {
	class DLL FormListener
	{
	public:
		FormListener(WNDPROC proc, char* id);
		int call(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		WNDPROC Proc;
		char* Id;
		char* getId();
	};
}

