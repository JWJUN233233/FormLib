#pragma once
#include <Windows.h>

namespace FormLib {
	class FormListener
	{
	public:
		FormListener(WNDPROC proc, char* id);
		void call(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		WNDPROC Proc;
		char* Id;
		char* getId();
	};
}

