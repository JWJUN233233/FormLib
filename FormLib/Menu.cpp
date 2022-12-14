#include "Menu.h"
using namespace FormLib;
Menu::Menu()
{
	owner = nullptr;
	hmenu = CreateMenu();
	listener = EmptyEvent;
}
HMENU Menu::getHMENU()
{
	return hmenu;
}
MenuNode* Menu::addMenu(Achar* Text, DWORD sytle)
{
	MenuNode* node = new MenuNode(hmenu, Text, sytle);
	nodes.push_back(node);
	AppendMenu(hmenu, sytle, node->id, Text);
	if (owner != nullptr) {
		owner->updata();
	}
	return node;
}
MenuNode* FormLib::Menu::addPopupMenu(Achar* Text, DWORD sytle)
{
	MenuNode* node = new MenuNode(CreatePopupMenu(), Text, MF_POPUP | sytle, true);
	nodes.push_back(node);
	AppendMenu(hmenu, MF_POPUP | sytle, (UINT)node->parent, Text);
	if (owner != nullptr) {
		owner->updata();
	}
	return node;
}
MenuNode* FormLib::Menu::addMenuItem(Achar* Text, MenuNode* PopupMenu, DWORD sytle)
{
	if (PopupMenu->IsPopupMenu) {
		MenuNode* node = new MenuNode(PopupMenu->parent, Text, sytle);
		nodes.push_back(node);
		AppendMenu(PopupMenu->parent, sytle, node->id, Text);
		if (owner != nullptr) {
			owner->updata();
		}
		return node;
	}
	return nullptr;
}
void FormLib::Menu::addMenuItem(MenuNode* node, MenuNode* PopupMenu)
{
	if (PopupMenu->IsPopupMenu) {
		nodes.push_back(node);
		if (node->IsPopupMenu) {
			Achar tmp[MAX_PATH];
			node->getText(tmp);
			AppendMenu(PopupMenu->parent, node->sytle, (UINT)node->parent, tmp);
		}
		else {
			Achar tmp[MAX_PATH];
			node->getText(tmp);
			AppendMenu(PopupMenu->parent, node->sytle, node->id, tmp);
		}
		if (owner != nullptr) {
			owner->updata();
		}
	}
}
MenuNode* Menu::insertMenu(Achar* Text, int location, DWORD sytle)
{
	MenuNode* node = new MenuNode(hmenu, Text, sytle);
	nodes.push_back(node);
	MENUITEMINFO info;
	info.cbSize = sizeof(info);
	info.fMask = MIIM_ID | MIIM_FTYPE | MIIM_DATA;
	info.fType = sytle;
	info.wID = node->id;
	info.hSubMenu = NULL;
	info.hbmpChecked = NULL;
	info.hbmpUnchecked = NULL;
	info.dwTypeData = Text;
	InsertMenuItem(hmenu, location, true, &info);
	node->setText(Text);
	if (owner != nullptr) {
		owner->updata();
	}
	return node;
}
void FormLib::Menu::insertMenu(MenuNode* node, int location)
{
	nodes.push_back(node);
	Achar tmp[MAX_PATH];
	node->getText(tmp);
	if (node->IsPopupMenu) {
		InsertMenu(hmenu, location, MF_BYPOSITION | node->sytle, (UINT)node->parent, tmp);
		node->setPopupText(hmenu, tmp);
	}
	else {
		InsertMenu(hmenu, location, MF_BYPOSITION | node->sytle, node->id, tmp);
		node->setText(tmp);
	}
	if (owner != nullptr) {
		owner->updata();
	}
}
void Menu::removeMenu(MenuNode* node)
{
	nodes.remove(node);
	if (!node->IsPopupMenu) {
		DeleteMenu(hmenu, node->id, node->sytle);
	}
	if (node->IsPopupMenu) {
		std::list<MenuNode*> tmp;
		for (auto& i : nodes) {
			if (i->parent == node->parent) {
				tmp.push_back(i);
			}
		}
		for (auto& i : tmp) {
			removeMenu(i);
		}
		DeleteMenu(hmenu, (UINT)node->parent, node->sytle);
		DestroyMenu(node->parent);
	}
	if (owner != nullptr) {
		owner->updata();
	}
	delete node;
}
void FormLib::Menu::removeMenu(int id)
{
	removeMenu(getNode(id));
}
MenuNode* FormLib::Menu::getNode(int id)
{
	for (auto& i : nodes) {
		if (i->id == id) {
			return i;
		}
	}
	return nullptr;
}
Form* Menu::getOwner()
{
	return owner;
}
void FormLib::Menu::setEventListener(EventProc Listener)
{
	listener = Listener;
}
MenuNode* FormLib::Menu::createPopupMenu(Achar* Text, DWORD sytle)
{
	return new MenuNode(CreatePopupMenu(), Text, MF_POPUP | sytle, true);
}
void FormLib::Menu::setOwner(Form* Owner)
{
	owner = Owner;
}
void Menu::onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COMMAND) {
		int id = LOWORD(wParam);
		for (auto& i : nodes) {
			if (i->id == id) {
				MenuClickEvent* e = new MenuClickEvent(hwnd, this, id);
				listener(e);
				delete e;
				return;
			}
		}
	}
}
MenuNode::MenuNode(HMENU _parent, Achar* _Text, DWORD _sytle, bool isPopupMenu)
{
	id = NextControlid;
	NextControlid++;
	parent = _parent;
	sytle = _sytle;
	IsPopupMenu = isPopupMenu;
	Text = _Text;
}
MenuNode::~MenuNode()
{
	
}
void MenuNode::setText(Achar* _Text)
{
	ModifyMenu(parent, id, sytle, id, _Text);
	Text = _Text;
}
void FormLib::MenuNode::setPopupText(HMENU _parent, Achar* _Text)
{
	ModifyMenu(_parent, id, sytle, id, _Text);
	Text = _Text;
}
void MenuNode::getText(Achar* out)
{
	if (!IsPopupMenu) {
		GetMenuString(parent, id, out, MAX_PATH, sytle);
	}
	else {
		wsprintf(out, Text);
	}
}

bool FormLib::MenuNode::isPopupMenu()
{
	return IsPopupMenu;
}
