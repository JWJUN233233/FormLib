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
	listener = NULL;
	showingHandler = NULL;
	hidingHandler = NULL;
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
	ShowingEvent* e = new ShowingEvent(this);
	if (listener != NULL) {
		listener(e);
	}
	if (showingHandler != NULL) {
		showingHandler(e);
	}
	if (!e->isCancel()) {
		ShowWindow(handle, SW_SHOW);
		UpdateWindow(handle);
	}
	delete e;
}
void FormLib::TextBox::hide()
{
	HidingEvent* e = new HidingEvent(this);
	if (listener != NULL) {
		listener(e);
	}
	if (hidingHandler != NULL) {
		hidingHandler(e);
	}
	if (!e->isCancel()) {
		ShowWindow(handle, SW_HIDE);
		UpdateWindow(handle);
	}
	delete e;
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
	if (enable) {
		EnableEvent* e = new EnableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		if (listener != NULL) {
			listener(e);
			if (!e->isCancel()) {
				Edit_Enable(handle, enable);
			}
		}
		delete e;
	}
	else {
		DisableEvent* e = new DisableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		if (listener != NULL) {
			listener(e);
			if (!e->isCancel()) {
				Edit_Enable(handle, enable);
			}
		}
		delete e;
	}
}
bool FormLib::TextBox::isEnable()
{
	return IsWindowEnabled(handle);
}
bool FormLib::TextBox::isMultiLine()
{
	return getSytle() & ES_MULTILINE;
}
void FormLib::TextBox::setIsMulitLine(bool isMulitLine)
{
	if (isMulitLine) {
		if (!isMultiLine()) {
			DWORD sytle = getSytle();
			Achar text[MAX_PATH];
			getText(text);
			destroy();
			_sytle = sytle | ES_MULTILINE | WS_BORDER;
			onCreate(getOwner()->GetHWND());
			setText(text);
		}
	}
	else {
		if (isMultiLine()) {
			if (!isMultiLine()) {
				DWORD sytle = getSytle();
				Achar text[MAX_PATH];
				getText(text);
				destroy();
				_sytle = sytle ^ ES_MULTILINE;
				onCreate(getOwner()->GetHWND());
				setText(text);
			}
		}
	}
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
void FormLib::TextBox::setEventListener(EventHandler Listener)
{
	listener = Listener;
}