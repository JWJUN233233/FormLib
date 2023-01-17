#include "CheckBox.h"

using namespace FormLib;
FormLib::CheckBox::CheckBox(Point point, Size size, DWORD sytle)
{
	_point = point;
	_size = size;
	controlID = NULL;
	handle = NULL;
	listener = NULL;
	clickHandler = NULL;
	cursorEnteringHandler = NULL;
	cursorLeavingHandler = NULL;
	showingHandler = NULL;
	hidingHandler = NULL;
	_sytle = sytle;
}
void FormLib::CheckBox::onCreate(HWND hwnd)
{
	handle = CreateWindow(_T("button"), _T(""), _sytle,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		hwnd, (HMENU)NextControlid, GetModuleHandle(0), NULL);
	controlID = NextControlid;
	NextControlid++;
	show();
}
void FormLib::CheckBox::show()
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
void FormLib::CheckBox::hide()
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
void FormLib::CheckBox::setPoint(Point point)
{
	MoveWindow(handle, point.GetX(), point.GetY(),
		_size.GetW(), _size.GetH(), true);
	_point = point;
}
void FormLib::CheckBox::setSize(Size size)
{
	MoveWindow(handle, _point.GetX(), _point.GetY(),
		size.GetW(), size.GetH(), true);
	_size = size;
}
Point FormLib::CheckBox::getPoint()
{
	return _point;
}
Size FormLib::CheckBox::getSize()
{
	return _size;
}
void FormLib::CheckBox::setText(Achar* Text)
{
	SetWindowText(handle, Text);
}
void FormLib::CheckBox::getText(Achar* out)
{
	GetWindowText(handle, out, MAX_PATH);
}
void FormLib::CheckBox::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COMMAND) {
		int id = LOWORD(wParam);
		if (id == controlID) {
			Form* owner = getOwner();
			Point p = owner->getPoint();
			CheckBoxClickEvent* e = nullptr;
			IControl* control = nullptr;
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				e = new CheckBoxClickEvent(hwnd, p, this);
				if (listener != NULL) {
					listener(e);
				}
				if (clickHandler != NULL) {
					clickHandler(e);
				}
				control = e->getOwner();
				if (!e->isCancel()) {
					((CheckBox*)control)->setCheck(!((CheckBox*)control)->isCheck());
				}
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
					if (listener != NULL) {
						listener(e);
					}
					if (cursorLeavingHandler != NULL) {
						cursorLeavingHandler((CursorLeavingEvent*)e);
					}
					delete e;
				}
				else if (pnmbchotitem->dwFlags == HICF_ENTERING) {
					e = new CursorEnteringEvent(hwnd, p, this);
					if (listener != NULL) {
						listener(e);
					}
					if (cursorEnteringHandler != NULL) {
						cursorEnteringHandler((CursorEnteringEvent*)e);
					}
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
void FormLib::CheckBox::destroy()
{
	DestroyWindow(handle);
}
void FormLib::CheckBox::setEnable(bool enable)
{
	if (enable) {
		EnableEvent* e = new EnableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		if (listener != NULL) {
			listener(e);
		}
		if (!e->isCancel()) {
			Button_Enable(handle, enable);
		}
		delete e;
	}
	else {
		DisableEvent* e = new DisableEvent(getOwner()->GetHWND(), getOwner()->getPoint(), this);
		if (listener != NULL) {
			listener(e);
		}
		if (!e->isCancel()) {
			Button_Enable(handle, enable);
		}
		delete e;
	}
}
bool FormLib::CheckBox::isEnable()
{
	return IsWindowEnabled(handle);
}
bool FormLib::CheckBox::isCheck()
{
	DWORD check = SendMessage(handle, BM_GETCHECK, 0, 0);
	return check == BST_CHECKED;
}
void FormLib::CheckBox::setCheck(bool isCheck)
{
	if (isCheck) {
		SendMessage(handle, BM_SETCHECK, BST_CHECKED, 0);
	}
	else {
		SendMessage(handle, BM_SETCHECK, BST_UNCHECKED, 0);
	}
}
int FormLib::CheckBox::getID()
{
	return controlID;
}
HWND FormLib::CheckBox::getHWND()
{
	return handle;
}
DWORD FormLib::CheckBox::getSytle()
{
	return GetWindowLong(handle, GWL_STYLE);
}
void FormLib::CheckBox::setSytle(DWORD sytle)
{
	SetWindowLong(handle, GWL_STYLE, sytle);
}
void FormLib::CheckBox::setEventListener(EventHandler Listener)
{
	listener = Listener;
}
