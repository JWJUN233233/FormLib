#include "Progress.h"
#include <iostream>
using namespace FormLib;
FormLib::Progress::Progress(Point point, Size size, DWORD sytle)
{
	_point = point;
	_size = size;
	controlID = NULL;
	handle = NULL;
	listener = NULL;
	showingHandler = NULL;
	hidingHandler = NULL;
	_sytle = sytle;
	range = PBRANGE();
}
void FormLib::Progress::onCreate(HWND hwnd)
{
	handle = CreateWindow(PROGRESS_CLASS, _T(""), _sytle,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		hwnd, (HMENU)NextControlid, GetModuleHandle(0), NULL);
	controlID = NextControlid;
	NextControlid++;
	show();
	setRange(0, 100);
	setStep(10);
}
void FormLib::Progress::show()
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
void FormLib::Progress::hide()
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
void FormLib::Progress::setPoint(Point point)
{
	MoveWindow(handle, point.GetX(), point.GetY(),
		_size.GetW(), _size.GetH(), true);
	_point = point;
}
void FormLib::Progress::setSize(Size size)
{
	MoveWindow(handle, _point.GetX(), _point.GetY(),
		size.GetW(), size.GetH(), true);
	_size = size;
}
void FormLib::Progress::setRange(int low, int high)
{
	SendMessage(handle, PBM_SETRANGE,    //设置进度条的范围
		(WPARAM)0, (LPARAM)(MAKELPARAM(low, high)));

	SendMessage(handle, PBM_GETRANGE,    //获取进度条的范围
		(WPARAM)TRUE,                    //TRUE 表示返回值为范围的最小值,FALSE表示返回最大值
		(LPARAM)&range);
}
PBRANGE FormLib::Progress::getRange()
{
	SendMessage(handle, PBM_GETRANGE,    //获取进度条的范围
		(WPARAM)TRUE,                    //TRUE 表示返回值为范围的最小值,FALSE表示返回最大值
		(LPARAM)&range);
	return range;
}
void FormLib::Progress::setPos(int pos)
{
	SendMessage(handle, PBM_SETPOS, (WPARAM)range.iLow, (LPARAM)pos);
}
int FormLib::Progress::getPos()
{
	return SendMessage(handle, PBM_GETPOS, (WPARAM)0, (LPARAM)0);
}
void FormLib::Progress::setStep(int pos)
{
	SendMessage(handle, PBM_SETSTEP,
		(WPARAM)(pos), (LPARAM)0);
}
void FormLib::Progress::setState(int state)
{
	SendMessage(handle, PBM_SETSTATE, state, (LPARAM)0);
}
int FormLib::Progress::getState()
{
	return SendMessage(handle, PBM_GETSTATE, (WPARAM)0, (LPARAM)0);
}
void FormLib::Progress::step()
{
	SendMessage(handle, PBM_STEPIT, (WPARAM)0, (LPARAM)0);
}
void FormLib::Progress::back()
{
	SendMessage(handle, PBM_STEPIT, (WPARAM)0, (LPARAM)0);
}
void FormLib::Progress::add(int pos)
{
	SendMessage(handle, PBM_DELTAPOS,
		(WPARAM)(pos), (LPARAM)0);
}
Point FormLib::Progress::getPoint()
{
	return _point;
}
Size FormLib::Progress::getSize()
{
	return _size;
}
void FormLib::Progress::setText(Achar* Text)
{
	SetWindowText(handle, Text);
}
void FormLib::Progress::getText(Achar* out)
{
	GetWindowText(handle, out, MAX_PATH);
}
void FormLib::Progress::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COMMAND) {

	}
	if (Message == WM_NOTIFY) {

	}
}
void FormLib::Progress::destroy()
{
	DestroyWindow(handle);
}
void FormLib::Progress::setEnable(bool enable)
{
	if (enable) {
		setState(PBST_NORMAL);
	}
	else {
		setState(PBST_PAUSED);
	}
}
bool FormLib::Progress::isEnable()
{
	return IsWindowEnabled(handle);
}
int FormLib::Progress::getID()
{
	return controlID;
}
HWND FormLib::Progress::getHWND()
{
	return handle;
}
DWORD FormLib::Progress::getSytle()
{
	return GetWindowLong(handle, GWL_STYLE);
}
void FormLib::Progress::setSytle(DWORD sytle)
{
	SetWindowLong(handle, GWL_STYLE, sytle);
}
void FormLib::Progress::setEventListener(EventHandler Listener)
{
	listener = Listener;
}

