#pragma once
#include "IControl.h"
namespace FormLib{
class Control :
    public IControl
{
	void onCreate(HWND hwnd);
	void Show();
	void Hide();
	void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	void Destroy();
	void setText(std::string Text);
	void getText(char** out);
	void setEnable(bool enable);
	int getID();
	bool isEnable();
};
}

