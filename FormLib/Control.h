#pragma once
#include "pch.h"
#include "IControl.h"
namespace FormLib{
class Control :
    public IControl
{
public:
	void onCreate(HWND hwnd);
	void Show();
	void Hide();
	void setText(Achar* Text);
	void getText(Achar* out);
	void setEnable(bool enable);
	int getID();
	bool isEnable();
private:
	void Destroy();
	void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
};
}

