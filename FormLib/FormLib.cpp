#include "Form.h"
#include "Button.h"
#include "pch.h"
#include "IColorfulOut.h"
#include "Progress.h"
using namespace FormLib;
using namespace DG_CoreLib;
Button* button;
Button* button2;
Button* button3;
MenuNode* popupMenu1;
MenuNode* P_NORMAL;
MenuNode* P_PAUSED;
MenuNode* P_ERROR;
MenuNode* B_ENABLE;
MenuNode* B_DISABLE;
Progress* progress;
Menu* menu;
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
        e2->getOwner()->setText((Achar*)_T("我被双击了"));
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
            e2->getOwner()->setText((Achar*)_T("启用这些控件"));
        }
        else {
            enable = true;
            e2->getOwner()->setText((Achar*)_T("禁用这些控件"));
        }
        button->setEnable(enable);
        button2->setEnable(enable);
        progress->setEnable(enable);
    }
}
void Button4Proc(IEvent* e) {
    char tmp[MAX_PATH] = "";
    e->getEventType(tmp);
    std::string stmp = tmp;
    if (stmp == "ButtonClickEvent") {
        FormLib::ButtonClickEvent* e2 = (ButtonClickEvent*)e;
    }
    else if (stmp == "CursorEnteringEvent") {
        FormLib::CursorEnteringEvent* e2 = (CursorEnteringEvent*)e;
        e2->getOwner()->setText((Achar*)_T("进入了按钮"));
    }
    else if (stmp == "CursorLeavingEvent") {
        FormLib::CursorLeavingEvent* e2 = (CursorLeavingEvent*)e;
        e2->getOwner()->setText((Achar*)_T("离开了按钮"));
    }
}
void MenuProc(IEvent* e) {
    char tmp[MAX_PATH] = "";
    e->getEventType(tmp);
    std::string stmp = tmp;
    if (stmp == "MenuClickEvent") {
        FormLib::MenuClickEvent* e2 = (MenuClickEvent*)e;
        if (e2->getNode() == P_NORMAL) {
            progress->setState(PBST_NORMAL);
        }
        if (e2->getNode() == P_PAUSED) {
            progress->setState(PBST_PAUSED);
        }
        if (e2->getNode() == P_ERROR) {
            progress->setState(PBST_ERROR);
        }
        if (e2->getNode() == B_DISABLE) {
            button->setEnable(false);
            button2->setEnable(false);
            button3->setEnable(false);
        }
        if (e2->getNode() == B_ENABLE) {
            button->setEnable(true);
            button2->setEnable(true);
            button3->setEnable(true);
        }
    }
}
int main()
{
    Achar* text = (Achar*)_T("中文测试");
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
    menu = new Menu();
    menu->setEventListener(MenuProc);
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
    button3->setText((Achar*)_T("禁用这些控件"));
    progress->setText((Achar*)_T("这是一个进度条"));
    f.Show();
    f.setBigIcon(icon);
    f.setSmallIcon(icon);
    f.addListener(listener);
    popupMenu1 = menu->addPopupMenu((Achar*)_T("管理控件"));
    P_NORMAL = menu->addMenuItem((Achar*)_T("设置Progress控件为PBST_NORMAL"), popupMenu1);
    P_PAUSED = menu->addMenuItem((Achar*)_T("设置Progress控件为PBST_PAUSED"), popupMenu1);
    P_ERROR = menu->addMenuItem((Achar*)_T("设置Progress控件为PBST_ERROR"), popupMenu1);
    B_DISABLE = menu->addMenuItem((Achar*)_T("禁用所有按钮"), popupMenu1);
    B_ENABLE = menu->addMenuItem((Achar*)_T("启用所有按钮"), popupMenu1);
    f.setMenu(menu);
    Form::Event();
    delete button;
    delete button2;
    delete button3;
    delete progress;
}