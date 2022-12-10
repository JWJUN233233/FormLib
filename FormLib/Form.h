#pragma once
#include "pch.h"
#include <Windows.h>
#include <string>
#include <list>
#include <map>
#include "Point.h"
#include "Size.h"
#include "FormListener.h"
#include "utils.h"
#include "Logger.h"
#include "Control.h"
#include <iostream>
#include "Res.h"
#pragma comment(lib, "Comctl32")
#include <CommCtrl.h>
using namespace DG_CoreLib;
namespace FormLib{
class Form
{
	public:
		Form(DG_CoreLib::Point location, DG_CoreLib::Size _size, achar* _Caption = (achar*)_T("Caption"));
		~Form();
		void Show();
		void Hide();
		static void Event();
		void setPoint(Point point);
		void setSize(Size size);
		Point getPoint();
		Size getSize();
		void SetCaption(achar* _Caption);
		void addListener(FormListener _listener);
		void setSmallIcon(HICON icon);
		void setBigIcon(HICON icon);
		void addControl(IControl* control);
		void removeControl(IControl* control);
		void ShowDialog(HWND dialog);
		void ShowDialog(Form dialog);
		LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		HWND GetHWND();
		static Form* FromHWND(HWND hwnd);
		static void Init();
	protected:
	private:
		HWND hwnd;
		Point _point;
		Size _size;
		achar* Caption;
		std::list<FormListener> listeners;
		std::list<IControl*> controls;
		HICON smallIcon;
		HICON bigIcon;
};
}