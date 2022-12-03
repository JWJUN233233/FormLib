#pragma once
#include "IControl.h"
#include <windowsx.h>
#include <string>
namespace FormLib {

    class Button :
        public IControl
    {
    public:
        Button(Point point, Size size);
        void onCreate(HWND hwnd);
        void Show();
        void Hide();
        void setPoint(Point point);
        void setSize(Size size);
        void setText(std::string Text);
        void getText(char** out);
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void Destroy();
        void setEnable(bool enable);
        bool isEnable();
        int getID();
    private:
        HWND handle;
        int controlID;
        Point _point;
        Size _size;
    };
}

