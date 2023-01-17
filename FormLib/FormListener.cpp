#include "FormListener.h"

namespace FormLib {
	FormListener::FormListener(WNDPROC proc, char* id) {
		Proc = proc;
		Id = id;
	}
	int FormListener::call(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return Proc(hwnd, Message, wParam, lParam);
	}
	char* FormListener::getId()
	{
		return Id;
	}
}