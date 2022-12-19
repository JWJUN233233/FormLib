#pragma once
#include "IControl.h"
namespace FormLib{
    class DLL TextBox : public IControl
    {
        friend class Form;
    public:
        TextBox(Point point, Size size, DWORD sytle = WS_BORDER | WS_CHILD | ES_LEFT | WS_TABSTOP);
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
