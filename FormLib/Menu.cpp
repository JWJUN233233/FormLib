#include "Menu.h"
using namespace FormLib;
Menu::Menu()
{
	owner = nullptr;
	hmenu = CreateMenu();
	listener = NULL;
}
HMENU Menu::getHMENU()
{
	return hmenu;
}
MenuItem* Menu::addMenu(Achar* Text, DWORD sytle)
{
	MenuItem* node = new MenuItem(hmenu, Text, sytle);
	nodes.push_back(node);
	AppendMenu(hmenu, sytle, node->id, Text);
	if (owner != nullptr) {
		owner->updata();
	}
	return node;
}
MenuItem* FormLib::Menu::addPopupMenu(Achar* Text, DWORD sytle)
{
	MenuItem* node = new MenuItem(CreatePopupMenu(), Text, MF_POPUP | sytle, true);
	nodes.push_back(node);
	AppendMenu(hmenu, MF_POPUP | sytle, (UINT)node->parent, Text);
	if (owner != nullptr) {
		owner->updata();
	}
	return node;
}
MenuItem* FormLib::Menu::addMenuItem(Achar* Text, MenuItem* PopupMenu, DWORD sytle)
{
	if (PopupMenu->IsPopupMenu) {
		MenuItem* node = new MenuItem(PopupMenu->parent, Text, sytle);
		nodes.push_back(node);
		AppendMenu(PopupMenu->parent, sytle, node->id, Text);
		if (owner != nullptr) {
			owner->updata();
		}
		return node;
	}
	return nullptr;
}
void FormLib::Menu::addMenuItem(MenuItem* node, MenuItem* PopupMenu)
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
MenuItem* Menu::insertMenu(Achar* Text, int location, DWORD sytle)
{
	MenuItem* node = new MenuItem(hmenu, Text, sytle);
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
void FormLib::Menu::insertMenu(MenuItem* node, int location)
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
void Menu::removeMenu(MenuItem* node)
{
	nodes.remove(node);
	if (!node->IsPopupMenu) {
		DeleteMenu(hmenu, node->id, node->sytle);
	}
	if (node->IsPopupMenu) {
		std::list<MenuItem*> tmp;
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
MenuItem* FormLib::Menu::getNode(int id)
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
void FormLib::Menu::setEventListener(EventHandler Listener)
{
	listener = Listener;
}
MenuItem* FormLib::Menu::createPopupMenu(Achar* Text, DWORD sytle)
{
	return new MenuItem(CreatePopupMenu(), Text, MF_POPUP | sytle, true);
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
				if (listener != NULL) {
					listener(e);
				}
				MenuItem* node = e->getNode();
				if (node->isCheckBox()) {
					if (!e->isCancel()) {
						node->setIsCheck(!node->isCheck());
					}
				}
				delete e;
				return;
			}
		}
	}
}
MenuItem::MenuItem(HMENU _parent, Achar* _Text, DWORD _sytle, bool isPopupMenu)
{
	id = NextControlid;
	NextControlid++;
	parent = _parent;
	sytle = _sytle;
	IsPopupMenu = isPopupMenu;
	Text = _Text;
	IsCheckBox = false;
}
MenuItem::~MenuItem()
{
	
}
void MenuItem::setText(Achar* _Text)
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	ModifyMenu(parent, id, Flag, id, _Text);
	Text = _Text;
}
void FormLib::MenuItem::setPopupText(HMENU _parent, Achar* _Text)
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	ModifyMenu(_parent, id, Flag, id, _Text);
	Text = _Text;
}
void FormLib::MenuItem::setIsCheckBox(bool isCheckBox)
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	if (isCheckBox) {
		ModifyMenu(parent, id, Flag | MF_CHECKED, id, Text);
	}
	else {
		ModifyMenu(parent, id, Flag, id, Text);
	}
	IsCheckBox = isCheckBox;
}
bool FormLib::MenuItem::isCheckBox()
{
	return IsCheckBox;
}
void FormLib::MenuItem::setIsCheck(bool isCheck)
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	if (isCheck and !(Flag & MF_CHECKED)) {
		ModifyMenu(parent, id, Flag | MF_CHECKED, id, Text);
	}
	else {
		if (Flag & MF_CHECKED) {
			ModifyMenu(parent, id, Flag ^ MF_CHECKED | MF_UNCHECKED, id, Text);
		}
	}
}
bool FormLib::MenuItem::isCheck()
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	return (Flag & MF_CHECKED);
}
void FormLib::MenuItem::setEnable(bool isEnable)
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	if (isEnable) {
		if (Flag & (MF_DISABLED | MF_GRAYED)) {
			ModifyMenu(parent, id, Flag ^ MF_DISABLED | MF_ENABLED, id, Text);
		}
	}
	else {
		if (!(Flag & (MF_DISABLED | MF_GRAYED))) {
			ModifyMenu(parent, id, Flag ^ MF_ENABLED | MF_DISABLED, id, Text);
		}
	}
}
bool FormLib::MenuItem::isEnable()
{
	DWORD Flag = GetMenuState(parent, id, MF_BYCOMMAND);
	return Flag & MF_ENABLED;
}
void MenuItem::getText(Achar* out)
{
	if (!IsPopupMenu) {
		GetMenuString(parent, id, out, MAX_PATH, sytle);
	}
	else {
		wsprintf(out, Text);
	}
}

bool FormLib::MenuItem::isPopupMenu()
{
	return IsPopupMenu;
}
