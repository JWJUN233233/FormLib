#pragma once
#include "IControl.h"
namespace FormLib{
    class TextBox : public IControl
    {
        friend class Form;
    public:
        TextBox(Point point, Size size, DWORD sytle = WS_CHILD | ES_WANTRETURN | WS_BORDER | WS_VISIBLE);
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
        bool isMultiLine();
        void setIsMulitLine(bool isMulitLine);
        int getID();
        HWND getHWND();
        DWORD getSytle();
        void setSytle(DWORD sytle);
        void setEventListener(EventHandler Listener);
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
