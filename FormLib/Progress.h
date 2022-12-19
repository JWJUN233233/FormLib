#pragma once
#include "pch.h"
#include "IControl.h"
#include <CommCtrl.h>
namespace FormLib {
    class DLL Progress :
        public IControl
    {
        friend class Form;
    public:
        Progress(Point point, Size size, DWORD sytle = WS_CHILD | PBS_SMOOTH);
        void onCreate(HWND hwnd);
        void show();
        void hide();
        void setPoint(Point point);
        void setSize(Size size);
        void setRange(int low, int high);
        PBRANGE getRange();
        void setPos(int pos);
        int getPos();
        void setStep(int pos);
        /*PBST_NORMAL为正常， PBST_ERROR为错误， PBST_PAUSED为暂停*/
        void setState(int state);
        /*PBST_NORMAL为正常， PBST_ERROR为错误， PBST_PAUSED为暂停*/
        int getState();
        void step();
        void back();
        void add(int pos);
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
        PBRANGE range;
        int controlID;
        Point _point;
        Size _size;
        DWORD _sytle;
        EventProc listener;
    };
}
