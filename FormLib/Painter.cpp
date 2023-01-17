#include "Painter.h"
#include "IControl.h"
namespace FormLib {
	Painter::Painter(Drawer drawer) {
		_drawer = drawer;
		id = NextControlid;
		NextControlid++;
	}
	void Painter::setDrawer(Drawer drawer)
	{
		_drawer = drawer;
	}
	int Painter::getId()
	{
		return id;
	}
	void Painter::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam, HDC hdc)
	{
		if (Message == WM_PAINT) {
			_drawer(hdc, hwnd);
		}
	}
}