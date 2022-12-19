#include "TextBox.h"
#include "Form.h"
#include <windowsx.h>

using namespace FormLib;
FormLib::TextBox::TextBox(Point point, Size size, DWORD sytle)
{
	_point = point;
	_size = size;
	controlID = NULL;
	handle = NULL;
	listener = EmptyEvent;
	_sytle = sytle;
}
void FormLib::TextBox::onCreate(HWND hwnd)
{
	handle = CreateWindow(_T("EDIT"), _T(""), _sytle,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		hwnd, (HMENU)NextControlid, GetModuleHandle(0), NULL);
	controlID = NextControlid;
	NextControlid++;
	show();
}
void FormLib::TextBox::show()
{
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}
void FormLib::TextBox::hide()
{
	ShowWindow(handle, SW_HIDE);
	UpdateWindow(handle);
}
void FormLib::TextBox::setPoint(Point point)
{
	MoveWindow(handle, point.GetX(), point.GetY(),
		_size.GetW(), _size.GetH(), true);
	_point = point;
}
void FormLib::TextBox::setSize(Size size)
{
	MoveWindow(handle, _point.GetX(), _point.GetY(),
		size.GetW(), size.GetH(), true);
	_size = size;
}
Point FormLib::TextBox::getPoint()
{
	return _point;
}
Size FormLib::TextBox::getSize()
{
	return _size;
}
void FormLib::TextBox::setText(Achar* Text)
{
	SetWindowText(handle, Text);
}
void FormLib::TextBox::getText(Achar* out)
{
	GetWindowText(handle, out, MAX_PATH);
}
void FormLib::TextBox::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COMMAND) {
		int id = LOWORD(wParam);
		if (id == controlID) {
			Form* owner = getOwner();
			Point p = owner->getPoint();
			IEvent* e = nullptr;
			switch (HIWORD(wParam))
			{

			}
		}
	}
	if (Message == SET_FOCUS) {

	}
	if (Message == KILL_FOCUS) {

	}
}
void FormLib::TextBox::destroy()
{
	DestroyWindow(handle);
}
void FormLib::TextBox::setEnable(bool enable)
{
	Edit_Enable(handle, enable);
	if (enable) {
		EnableEvent* e = new EnableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		listener(e);
		delete e;
	}
	else {
		DisableEvent* e = new DisableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		listener(e);
		delete e;
	}
}
bool FormLib::TextBox::isEnable()
{
	return IsWindowEnabled(handle);
}
int FormLib::TextBox::getID()
{
	return controlID;
}
HWND FormLib::TextBox::getHWND()
{
	return handle;
}
DWORD FormLib::TextBox::getSytle()
{
	return GetWindowLong(handle, GWL_STYLE);
}
void FormLib::TextBox::setSytle(DWORD sytle)
{
	SetWindowLong(handle, GWL_STYLE, sytle);
}
void FormLib::TextBox::setEventListener(EventProc Listener)
{
	listener = Listener;
}