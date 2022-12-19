#pragma once
#include "pch.h"
#include "IControl.h"
#include <windowsx.h>
#include <string>
#include "Form.h"
#include <CommCtrl.h>
namespace FormLib {
    class DLL Button :
        public IControl
    {
        friend class Form;
    public:
        Button(Point point, Size size, DWORD sytle = WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_TABSTOP);
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
        int getID();
        HWND getHWND();
        DWORD getSytle();
        void setSytle(DWORD sytle);
        void setEventListener(EventProc Listener);
    private:
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void destroy();
        HWND handle;
        int controlID;
        Point _point;
        Size _size;
        DWORD _sytle;
        EventProc listener;
    };
}

