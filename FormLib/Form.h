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
#pragma once
using namespace DG_CoreLib;
namespace FormLib{
class Form
{
	public:
		Form(DG_CoreLib::Point location, DG_CoreLib::Size _size, std::string _ClassName = "FormLib", std::string _Caption = "Caption");
		void Show();
		void Hide();
		void Updata();
		void Event();
		void setPoint(Point point);
		void setSize(Size size);
		void SetCaption(std::string _Caption);
		void addListener(FormListener _listener);
		void setSmallIcon(HICON icon);
		void setBigIcon(HICON icon);
		void addControl(IControl* control);
		void removeControl(IControl* control);
		LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		HWND GetHWND();
		static Form* FromHWND(HWND hwnd);
		static void Init();
	protected:
	private:
		WNDCLASSEX wc;
		HWND hwnd;
		MSG Msg;
		Point _point;
		Size _size;
		std::string Caption;
		std::string ClassName;
		bool IsCreated;
		std::list<FormListener> listeners;
		std::list<IControl*> controls;
		HICON smallIcon;
		HICON bigIcon;
};
}