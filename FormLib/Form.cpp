#include "Form.h"
#include "IColorfulOut.h"
#include <tchar.h>
#include <iostream>
#pragma once
using namespace FormLib;
using namespace std;
#define LS(strings) (LPCWSTR)toWchar_t(strings)
LRESULT WINAPI FormWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
std::map<HWND, Form*> hwnd_Form;
Form::Form(DG_CoreLib::Point location, DG_CoreLib::Size size,std::string _ClassName, std::string _Caption)
{
	_point = location;
	_size = size;
	ClassName = _ClassName;
	Caption = _Caption;
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = FormWinProc;
	wc.hInstance	 = GetModuleHandle (0);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = ClassName.c_str();
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	IsCreated = false;
}
void Form::Show(){
	if(IsCreated){
		return; 
	} 
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, _T("Window Registration Failed!")
			,_T("Error!"),MB_ICONEXCLAMATION|MB_OK);
		throw "Window Registration Failed!";
	}
		hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
			ClassName.c_str(),
			Caption.c_str(),
			WS_VISIBLE|WS_OVERLAPPEDWINDOW,
			_point.GetX(),_point.GetY(),
			_size.GetW(),_size.GetH(),
			NULL,NULL,GetModuleHandle (0), (LPVOID)this);
		if(hwnd == NULL) {
		MessageBox(NULL, _T("Window Creation Failed!")
			,_T("Error!"),MB_ICONEXCLAMATION|MB_OK);
		throw "Window Creation Failed!";
	}
		hwnd_Form[hwnd] = this;
	IsCreated = true;
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}
void Form::Hide(){
	if(IsCreated){
		SetWindowPos(hwnd,HWND_NOTOPMOST,
			_point.GetX(),_point.GetY(),
			_size.GetW(),_size.GetH(),SWP_HIDEWINDOW);
	}
}
void Form::Event(){
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
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
void Form::Updata(){
	if(IsCreated){
		SetWindowText(hwnd,Caption.c_str());
		MoveWindow(hwnd, _point.GetX(), _point.GetY(), _size.GetW(), _size.GetH(), true);
	}
}
void Form::SetCaption(std::string _Caption){
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
	control -> onCreate(hwnd);
	control -> setOwner((int)this);
	controls.push_back(control);
}
void FormLib::Form::removeControl(IControl* control)
{
	controls.remove(control);
}
HWND Form::GetHWND(){
	return hwnd;
}
Form* FormLib::Form::FromHWND(HWND hwnd)
{
	return hwnd_Form[hwnd];
}
void FormLib::Form::Init()
{
	hwnd_Form = {};
}
LRESULT FormLib::Form::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	for (auto& i : listeners) {
		i.call(hwnd, Message, wParam, lParam);
	}
	int h;
	int w;
	int xPos;
	int yPos;
	switch(Message)
	{
	case WM_MOVE:
		xPos = (int)(short)LOWORD(lParam);
		yPos = (int)(short)HIWORD(lParam);
		_point.SetPoint(xPos, yPos);
		break;
	case WM_SIZE:
		w = (int)(short)LOWORD(lParam);
		h = (int)(short)HIWORD(lParam);
		_size.SetSize(w, h);
		break;
	case WM_COMMAND:
		for (auto& i : controls) {
			i -> onFormCommand(hwnd, Message, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
		break;
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

