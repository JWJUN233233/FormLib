#pragma once
#include "pch.h"
#include <Windows.h>
namespace FormLib {
	typedef void (*Drawer)(HDC, HWND);
	class DLL Painter
	{
		friend class Form;
	public:
		Painter(Drawer drawer);
		void setDrawer(Drawer drawer);
		int getId();
	private:
		Drawer _drawer;
		int id;
		void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam, HDC hdc);
	};
}
