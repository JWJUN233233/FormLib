#pragma once
#include "pch.h"
#include <Windows.h>
#include "IControl.h"
#include "Form.h"
#include <list>
namespace FormLib {
    class MenuItem;
    class Menu : public IMenu
    {
        friend class Form;
    public:
        Menu();
        HMENU getHMENU();
        MenuItem* addMenu(Achar* Text, DWORD sytle = MF_STRING);
        MenuItem* addPopupMenu(Achar* Text, DWORD sytle = MF_STRING);
        MenuItem* addMenuItem(Achar* Text,MenuItem* PopupMenu, DWORD sytle = MF_STRING);
        void addMenuItem(MenuItem* node, MenuItem* PopupMenu);
        MenuItem* insertMenu(Achar* Text,int location, DWORD sytle = MF_STRING);
        void insertMenu(MenuItem* node, int location);
        void removeMenu(MenuItem* node);
        void removeMenu(int id);
        MenuItem* getNode(int id);
        Form* getOwner();
        void setEventListener(EventHandler Listener);
        static MenuItem* createPopupMenu(Achar* Text, DWORD sytle = MF_STRING);
    private:
        Form* owner;
        EventHandler listener;
        void setOwner(Form* owner);
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        HMENU hmenu;
        std::list<MenuItem*> nodes;
    };
    class MenuItem{
        friend class Menu;
    public:
        MenuItem(HMENU parent,Achar* Text, DWORD sytle = MF_STRING, bool isPopupMenu = false);
        void setText(Achar* Text);
        void setPopupText(HMENU parent, Achar* Text);
        void setIsCheckBox(bool isCheckBox);
        bool isCheckBox();
        void setIsCheck(bool isCheck);
        bool isCheck();
        void setEnable(bool isEnable);
        bool isEnable();
        void getText(Achar* out);
        bool isPopupMenu();
        ~MenuItem();
    private:
        int id;
        bool IsPopupMenu;
        bool IsCheckBox;
        HMENU parent;
        DWORD sytle;
        Achar* Text;
    };
}
