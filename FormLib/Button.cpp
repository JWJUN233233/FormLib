#include "Button.h"

FormLib::Button::Button(Point point, Size size)
{
	_point = point;
	_size = size;
	controlID = NULL;
	handle = NULL;
}

void FormLib::Button::onCreate(HWND hwnd)
{
	handle = CreateWindow("button", "", WS_CHILD | BS_PUSHBUTTON,
		_point.GetX(), _point.GetY(),
		_size.GetW(), _size.GetH(),
		hwnd, (HMENU)NextControlid, GetModuleHandle(0), NULL);
	controlID = NextControlid;
	NextControlid++;
}

void FormLib::Button::Show()
{
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}

void FormLib::Button::Hide()
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

void FormLib::Button::setText(std::string Text)
{
	SetWindowText(handle, Text.c_str());
}

void FormLib::Button::getText(char** out)
{
	GetWindowText(handle, *out, MAX_PATH);
}

void FormLib::Button::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);
	if (id == controlID) {
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			MessageBox(NULL, "Äãµã»÷ÁË°´Å¥", "message", MB_OK);
			setText("Clicked");
		}
	}
}

void FormLib::Button::Destroy()
{
	DestroyWindow(handle);
}

void FormLib::Button::setEnable(bool enable)
{
	Button_Enable(handle, enable);
}

bool FormLib::Button::isEnable()
{
	return IsWindowEnabled(handle);
}

int FormLib::Button::getID()
{
	return controlID;
}
