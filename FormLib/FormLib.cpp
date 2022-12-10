#include "Form.h"
#include "Button.h"
#include "pch.h"
#include "IColorfulOut.h"
#include "Progress.h"
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
using namespace FormLib;
using namespace DG_CoreLib;
Button* button;
Button* button2;
Button* button3;
Progress* progress;
bool enable = true;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        return 0;
    }
    return 0;
}
void ButtonProc(IEvent* e) {
    char tmp[MAX_PATH] = "";
    e -> getEventType(tmp);
    std::string stmp = tmp;
    if (stmp == "ButtonClickEvent") {
        FormLib::ButtonClickEvent* e2 = (ButtonClickEvent*)e;
        progress->setPos(0);
    }
}
void Button2Proc(IEvent* e) {
    char tmp[MAX_PATH] = "";
    e->getEventType(tmp);
    std::string stmp = tmp;
    if (stmp == "ButtonClickEvent") {
        FormLib::ButtonClickEvent* e2 = (ButtonClickEvent*)e;
        progress->step();
    }
    if (stmp == "ButtonDoubleClickEvent") {
        FormLib::ButtonDoubleClickEvent* e2 = (ButtonDoubleClickEvent*)e;
        e2->getOwner()->setText((achar*)_T("我被双击了"));
    }
}
void Button3Proc(IEvent* e) {
    char tmp[MAX_PATH] = "";
    e->getEventType(tmp);
    std::string stmp = tmp;
    if (stmp == "ButtonClickEvent") {
        FormLib::ButtonClickEvent* e2 = (ButtonClickEvent*)e;
        if (enable) {
            enable = false;
            e2->getOwner()->setText((achar*)_T("启用这些控件"));
        }
        else {
            enable = true;
            e2->getOwner()->setText((achar*)_T("禁用这些控件"));
        }
        button->setEnable(enable);
        button2->setEnable(enable);
        progress->setEnable(enable);
    }
}
int main()
{
    achar* text = (achar*)_T("中文测试");
    Point p(200,200);
    Size s(800,800);
    Form::Init();
    Point p2(60, 60);
    Size s2(100, 40);
    Point p3(200, 60);
    Size s3(60, 40);
    Point p4(500, 120);
    Size s4(200, 40);
    Point p5(60, 120);
    Size s5(100, 40);
    button = new Button(p2, s2);
    button->setEventListener(ButtonProc);
    button2 = new Button(p3, s2);
    button2->setEventListener(Button2Proc);
    button3 = new Button(p5, s5);
    button3->setEventListener(Button3Proc);
    Form f(p, s,text);
    progress = new Progress(p4, s4, WS_CHILD | PBS_SMOOTH);
    FormListener listener(WndProc, (char*)"tmp");
    HICON icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
    f.addControl(button);
    f.addControl(button2);
    f.addControl(button3);
    f.addControl(progress);
    button3->setText((achar*)_T("禁用这些控件"));
    progress->setText((achar*)_T("这是一个进度条"));
    f.Show();
    f.setBigIcon(icon);
    f.setSmallIcon(icon);
    f.addListener(listener);
    Form::Event();
    delete button;
}