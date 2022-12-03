#include <iostream>
#include <list>
#include "Form.h"
#include "Point.h"
#include "utils.h"
#include "IColorfulOut.h"
#include "Logger.h"
#include "Button.h"
#include "Res.h"
using namespace FormLib;
using namespace DG_CoreLib;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        MessageBox(hWnd, "你为什么要关！！！", "ERROR", MB_OK);
    }
    return 0;
}
int main()
{
    char text[MAX_PATH] = "中文测试";
    char retText[MAX_PATH] = { "\0" };
    utf8ToGbk(text, retText);
    Point p(600,600);
    Size s(600,400);
    Form::Init();
    Point p2(60, 60);
    Size s2(60, 40);
    Button* button = new Button(p2, s2);
    Form f(p, s, "FormLib",text);
    FormListener listener(WndProc, (char*)"tmp");
    HICON icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
    f.Show();
    f.setBigIcon(icon);
    f.setSmallIcon(icon);
    f.addListener(listener);
    f.addControl(button);
    button->Show();
    f.Event();
}