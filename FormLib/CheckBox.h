#pragma once
#include "IControl.h"
#include "Form.h"
#include <CommCtrl.h>
#include <Windows.h>
#include <windowsx.h>
namespace FormLib {
    class CheckBox : public IControl
    {
        friend class Form;
    public:
        CheckBox(Point point, Size size, DWORD sytle = WS_CHILD | BS_CHECKBOX | BS_NOTIFY | WS_TABSTOP);
        void onCreate(HWND hwnd);
        void show();
        void hide();
        void setPoint(Point point);
        void setSize(Size size);
        Point getPoint();
        Size getSize();
        void setText(Achar* Text);
        void getText(Achar* out);
        void setEnable(bool enable);
        bool isEnable();
        bool isCheck();
        void setCheck(bool isCheck);
        int getID();
        HWND getHWND();
        DWORD getSytle();
        void setSytle(DWORD sytle);
        void setEventListener(EventHandler Listener);
        CheckBoxClickEventHandler clickHandler;
        CursorEnteringEventHandler cursorEnteringHandler;
        CursorLeavingEventHandler cursorLeavingHandler;
        ShowingEventHandler showingHandler;
        HidingEventHandler hidingHandler;
    private:
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void destroy();
        HWND handle;
        int controlID;
        Point _point;
        Size _size;
        DWORD _sytle;
        EventHandler listener;
    };
}
