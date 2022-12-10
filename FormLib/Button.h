#pragma once
#include "pch.h"
#include "IControl.h"
#include <windowsx.h>
#include <string>
#include "Form.h"
#include <CommCtrl.h>
namespace FormLib {
    class Button :
        public IControl
    {
        friend class Form;
    public:
        Button(Point point, Size size, DWORD sytle = BS_NOTIFY | WS_CHILD | BS_PUSHBUTTON);
        void onCreate(HWND hwnd);
        void Show();
        void Hide();
        void setPoint(Point point);
        void setSize(Size size);
        Point getPoint();
        Size getSize();
        void setText(achar* Text);
        void getText(achar* out);
        void setEnable(bool enable);
        bool isEnable();
        int getID();
        void setEventListener(EventProc Listener);
    private:
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void Destroy();
        HWND handle;
        int controlID;
        Point _point;
        Size _size;
        DWORD _sytle;
        EventProc listener;
    };
}

