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
#include "Painter.h"
#include "Menu.h"
using namespace DG_CoreLib;
namespace FormLib{
class Form
{
	public:
		Form(DG_CoreLib::Point location, DG_CoreLib::Size _size, Achar* _Caption = (Achar*)_T("Caption"), DWORD sytle = WS_OVERLAPPEDWINDOW);
		~Form();
		void Show();
		void Hide();
		static void Event();
		void setPoint(Point point);
		void setSize(Size size);
		Point getPoint();
		Size getSize();
		void SetCaption(Achar* _Caption);
		void addListener(FormListener _listener);
		void setSmallIcon(HICON icon);
		void setBigIcon(HICON icon);
		void addControl(IControl* control);
		void removeControl(IControl* control);
		void addPainter(Painter* painter);
		void removePainter(Painter* painter);
		void ShowDialog(HWND dialog);
		void ShowDialog(Form dialog);
		void setSytle(DWORD sytle);
		void setMenu(IMenu* menu);
		IMenu* getMenu();
		void removeMenu();
		void updata();
		DWORD getSytle();
		LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		HWND GetHWND();
		void setTaskBar(bool isenable);
		bool isShowInTaskBar();
		static Form* FromHWND(HWND hwnd);
		static void Init();
	private:
		HWND hwnd;
		IMenu* menu;
		Point _point;
		Size _size;
		Achar* Caption;
		std::list<FormListener> listeners;
		std::list<IControl*> controls;
		std::list<Painter*> painters;
		HICON smallIcon;
		HICON bigIcon;
};
}