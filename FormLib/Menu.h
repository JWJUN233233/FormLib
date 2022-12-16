#pragma once
#include "pch.h"
#include <Windows.h>
#include "IControl.h"
#include "Form.h"
#include <list>
namespace FormLib {
    class MenuNode;
    class Menu : public IMenu
    {
        friend class Form;
    public:
        Menu();
        HMENU getHMENU();
        MenuNode* addMenu(Achar* Text, DWORD sytle = MF_STRING);
        MenuNode* addPopupMenu(Achar* Text, DWORD sytle = MF_STRING);
        MenuNode* addMenuItem(Achar* Text,MenuNode* PopupMenu, DWORD sytle = MF_STRING);
        void addMenuItem(MenuNode* node, MenuNode* PopupMenu);
        MenuNode* insertMenu(Achar* Text,int location, DWORD sytle = MF_STRING);
        void insertMenu(MenuNode* node, int location);
        void removeMenu(MenuNode* node);
        void removeMenu(int id);
        MenuNode* getNode(int id);
        Form* getOwner();
        void setEventListener(EventProc Listener);
        static MenuNode* createPopupMenu(Achar* Text, DWORD sytle = MF_STRING);
    private:
        Form* owner;
        EventProc listener;
        void setOwner(Form* owner);
        void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
        HMENU hmenu;
        std::list<MenuNode*> nodes;
    };
    class MenuNode {
        friend class Menu;
    public:
        MenuNode(HMENU parent,Achar* Text, DWORD sytle = MF_STRING, bool isPopupMenu = false);
        void setText(Achar* Text);
        void setPopupText(HMENU parent, Achar* Text);
        void getText(Achar* out);
        bool isPopupMenu();
        ~MenuNode();
    private:
        int id;
        bool IsPopupMenu;
        HMENU parent;
        DWORD sytle;
        Achar* Text;
    };
}
