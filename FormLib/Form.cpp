#include "Form.h"
#include "Button.h"
#include "IColorfulOut.h"
#include <tchar.h>
#include <iostream>
#include <cstdlib>
#pragma once
using namespace FormLib;
using namespace std;
LRESULT WINAPI FormWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
std::map<HWND, Form*> hwnd_Form;
Form::Form(DG_CoreLib::Point location, DG_CoreLib::Size size, Achar* _Caption, DWORD sytle)
{
	menu = nullptr;
	_point = location;
	_size = size;
	Caption = _Caption;
	smallIcon = NULL;
	bigIcon = NULL;
	/*focusControl = -1;*/
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
		_T("FormLib"),
		Caption,
		sytle,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		NULL, NULL, GetModuleHandle(0), (LPVOID)this);
	if (hwnd == NULL) {
		MessageBox(NULL, _T("Window Creation Failed!")
			, _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		throw "Window Creation Failed!";
	}
	hwnd_Form[hwnd] = this;
	UpdateWindow(hwnd);
}
FormLib::Form::~Form()
{
	DestroyWindow(hwnd);
	hwnd_Form.erase(hwnd);
}
void Form::show(){
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}
void Form::hide(){
	SetWindowPos(hwnd,HWND_NOTOPMOST,
	_point.GetX(),_point.GetY(),
	_size.GetW(),_size.GetH(),SWP_HIDEWINDOW);
}
void Form::Event(){
	MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		if (!IsDialogMessage(hwnd, &Msg))
		{
			TranslateMessage(&Msg);

			DispatchMessage(&Msg);
		}
	}
}
void FormLib::Form::setPoint(Point point)
{
	MoveWindow(hwnd, point.GetX(), point.GetY(), _size.GetW(), _size.GetH(), true);
}
void FormLib::Form::setSize(Size size)
{
	MoveWindow(hwnd, _point.GetX(), _point.GetY(), size.GetW(), size.GetH(), true);
}
Point FormLib::Form::getPoint()
{
	return _point;
}
Size FormLib::Form::getSize()
{
	return _size;
}
void Form::setCaption(Achar* _Caption){
	Caption = _Caption;
}
void FormLib::Form::addListener(FormListener _listener)
{
	listeners.push_back(_listener);
}
void FormLib::Form::setSmallIcon(HICON icon)
{
	smallIcon = icon;
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon);
}
void FormLib::Form::setBigIcon(HICON icon)
{
	bigIcon = icon;
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)bigIcon);
}
void FormLib::Form::addControl(IControl* control)
{
	if (control->getOwner() != NULL) {
		return;
	}
	control -> onCreate(hwnd);
	control -> setOwner(this);
	controls.push_back(control);
}
void FormLib::Form::removeControl(IControl* control)
{
	if (control->getOwner() == NULL) {
		return;
	}
	control->destroy();
	control->setOwner(NULL);
	controls.remove(control);
}
void FormLib::Form::addPainter(Painter* painter)
{
	painters.push_back(painter);
}
void FormLib::Form::removePainter(Painter* painter)
{
	painters.remove(painter);
}
void FormLib::Form::showDialog(HWND dialog)
{
}
void FormLib::Form::showDialog(Form dialog)
{
}
void FormLib::Form::flashWindow()
{
	FlashWindow(hwnd, true);
}
void FormLib::Form::setSytle(DWORD sytle)
{
	SetWindowLong(hwnd, GWL_STYLE, sytle);
}
void FormLib::Form::setMenu(IMenu* menu)
{
	SetMenu(hwnd, menu->getHMENU());
	this->menu = menu;
	menu->setOwner(this);
	updata();
}
IMenu* FormLib::Form::getMenu()
{
	return menu;
}
void FormLib::Form::removeMenu()
{
	SetMenu(hwnd, NULL);
	menu->setOwner(nullptr);
	this->menu = nullptr;
}
void FormLib::Form::updata()
{
	UpdateWindow(hwnd);
	DrawMenuBar(hwnd);
}
DWORD FormLib::Form::getSytle()
{
	return GetWindowLong(hwnd, GWL_STYLE);
}
HWND Form::GetHWND(){
	return hwnd;
}
void FormLib::Form::setTaskBar(bool isenable)
{
	DWORD oldSytle = GetWindowLong(hwnd, GWL_EXSTYLE);
	if (!isenable) {
		SetWindowLong(hwnd, GWL_EXSTYLE, oldSytle | WS_EX_TOOLWINDOW);
	}
	else {
		SetWindowLong(hwnd, GWL_EXSTYLE, oldSytle ^ WS_EX_TOOLWINDOW);
	}
}
bool FormLib::Form::isShowInTaskBar()
{
	return GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW;
}
Form* FormLib::Form::FromHWND(HWND hwnd)
{
	return hwnd_Form[hwnd];
}
void FormLib::Form::Init()
{
	hwnd_Form = {};
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = FormWinProc;
	wc.hInstance = GetModuleHandle(0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = _T("FormLib");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, _T("Window Registration Failed!")
			, _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		throw "Window Registration Failed!";
	}
	InitCommonControls();
}
LRESULT FormLib::Form::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	for (auto& i : listeners) {
		int tmp = i.call(hwnd, Message, wParam, lParam);
		if (tmp != 0) {
			return tmp;
		}
	}
	switch(Message)
	{
	case WM_MOVE:
		int xPos;
		int yPos;
		xPos = (int)(short)LOWORD(lParam);
		yPos = (int)(short)HIWORD(lParam);
		_point.SetPoint(xPos, yPos);
		break;
	case WM_SIZE:
		int h;
		int w;
		w = (int)(short)LOWORD(lParam);
		h = (int)(short)HIWORD(lParam);
		_size.SetSize(w, h);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		for (auto& i : painters) {
			i->_drawer(hdc, hwnd);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		/*if (wParam == VK_TAB) {
			focusControl++;
			if (focusControl >= controls.size() - 1) {
				focusControl = -1;
				SetForegroundWindow(hwnd);
				SetFocus(hwnd);
			}
			else {
				int c = 0;
				for (auto& i : controls) {
					if (c == focusControl) {
						i->onFormCommand(hwnd, SET_FOCUS, 0, 0);
						SetForegroundWindow(hwnd);
						SetFocus(i->getHWND());
						break;
					}
					if (c + 1 == focusControl) {
						i->onFormCommand(hwnd, KILL_FOCUS, 0, 0);
						SetForegroundWindow(hwnd);
					}
					c++;
				}
			};
		}*/
		break;
	case WM_COMMAND:
		for (auto& i : controls) {
			i -> onFormCommand(hwnd, Message, wParam, lParam);
		}
		if (menu != nullptr) {
			menu->onFormCommand(hwnd, Message, wParam, lParam);
		}
		break;
	case WM_NOTIFY:
		for (auto& i : controls) {
			i->onFormCommand(hwnd, Message, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
LRESULT WINAPI FormWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Form* pmyclass;
	pmyclass = Form::FromHWND(hwnd);
	switch (message)
	{
	case WM_DESTROY: {
		hwnd_Form.erase(hwnd);
	}
	}
	if (pmyclass != nullptr) {
		return pmyclass->WndProc(hwnd, message, wParam, lParam);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
