#pragma once
#include "Point.h"
#include "Size.h"
#include <Windows.h>
#include <string>
using namespace DG_CoreLib;
#pragma once
extern int NextControlid;
namespace FormLib {
	class IControl
	{
	public:
		IControl() { owner = 0; };
		void setOwner(int _owner);
		int getOwner();
		virtual void onCreate(HWND hwnd) = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) = 0;
		virtual void Destroy() = 0;
		virtual void setText(std::string Text) = 0;
		virtual void getText(char** out) = 0;
		virtual void setEnable(bool enable) = 0;
		virtual bool isEnable() = 0;
		virtual int getID() = 0;
	private:
		int owner;
		Point _point;
		Size _size;
	};
}