#include "Button.h"

using namespace FormLib;
FormLib::Button::Button(Point point, Size size, DWORD sytle)
{
	_point = point;
	_size = size;
	controlID = NULL;
	handle = NULL;
	listener = EmptyEvent;
	_sytle = sytle;
}
void FormLib::Button::onCreate(HWND hwnd)
{
	handle = CreateWindow(_T("button"), _T(""), _sytle,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		hwnd, (HMENU)NextControlid, GetModuleHandle(0), NULL);
	controlID = NextControlid;
	NextControlid++;
	show();
}
void FormLib::Button::show()
{
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}
void FormLib::Button::hide()
{
	ShowWindow(handle, SW_HIDE);
	UpdateWindow(handle);
}
void FormLib::Button::setPoint(Point point)
{
	MoveWindow(handle, point.GetX(), point.GetY(),
		_size.GetW(), _size.GetH(), true);
	_point = point;
}
void FormLib::Button::setSize(Size size)
{
	MoveWindow(handle, _point.GetX(), _point.GetY(),
		size.GetW(), size.GetH(), true);
	_size = size;
}
Point FormLib::Button::getPoint()
{
	return _point;
}
Size FormLib::Button::getSize()
{
	return _size;
}
void FormLib::Button::setText(Achar* Text)
{
	SetWindowText(handle, Text);
}
void FormLib::Button::getText(Achar* out)
{
	GetWindowText(handle, out, MAX_PATH);
}
void FormLib::Button::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
		if (Message == WM_COMMAND) {
		int id = LOWORD(wParam);
		if (id == controlID) {
			Form* owner = getOwner();
			Point p = owner->getPoint();
			IEvent* e = nullptr;
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				e = new ButtonClickEvent(hwnd, p, this);
				listener(e);
				delete e;
				break;
			case BN_DOUBLECLICKED:
				e = new ButtonDoubleClickEvent(hwnd, p, this);
				listener(e);
				delete e;
				break;
			}
		}
	}
	if (Message == WM_NOTIFY) {
		Form* owner = getOwner();
		Point p = owner->getPoint();
		IEvent* e = nullptr;
		LPNMHDR tmp = (LPNMHDR)lParam;
		if (tmp->idFrom == controlID) {
			NMBCHOTITEM* pnmbchotitem = (NMBCHOTITEM*)lParam;
			pnmbchotitem->dwFlags = pnmbchotitem->dwFlags - 1;
			switch (tmp->code) {
			case BCN_HOTITEMCHANGE:
				if (pnmbchotitem->dwFlags == HICF_LEAVING) {
					e = new CursorLeavingEvent(hwnd, p, this);
					listener(e);
					delete e;
				}
				else if (pnmbchotitem->dwFlags == HICF_ENTERING) {
					e = new CursorEnteringEvent(hwnd, p, this);
					listener(e);
					delete e;
				}
				break;
			}
		}
	}
	if (Message == SET_FOCUS) {
		//setSytle(_sytle | BS_DEFPUSHBUTTON);
	}
	if (Message == KILL_FOCUS) {
		//setSytle(_sytle | BS_PUSHBUTTON & BS_DEFPUSHBUTTON);
	}
}
void FormLib::Button::destroy()
{
	DestroyWindow(handle);
}
void FormLib::Button::setEnable(bool enable)
{
	Button_Enable(handle, enable);
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
bool FormLib::Button::isEnable()
{
	return IsWindowEnabled(handle);
}
int FormLib::Button::getID()
{
	return controlID;
}
HWND FormLib::Button::getHWND()
{
	return handle;
}
DWORD FormLib::Button::getSytle()
{
	return GetWindowLong(handle, GWL_STYLE);
}
void FormLib::Button::setSytle(DWORD sytle)
{
	SetWindowLong(handle, GWL_STYLE, sytle);
}
void FormLib::Button::setEventListener(EventProc Listener)
{
	listener = Listener;
}
