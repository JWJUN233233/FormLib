#pragma once
#include "pch.h"
#include "IControl.h"
namespace FormLib{
class DLL Control :
    public IControl
{
public:
	void onCreate(HWND hwnd);
	void show();
	void hide();
	void setText(Achar* Text);
	void getText(Achar* out);
	void setEnable(bool enable);
	int getID();
	bool isEnable();
private:
	void destroy();
	void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
};
}

