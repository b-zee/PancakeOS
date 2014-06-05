#include "Menu.h"

namespace zm {

Menu::Menu(const char *lpNewItem) : m_lpNewItem(lpNewItem) {
	m_hMenu = CreatePopupMenu();
}
void Menu::AddSubMenu(SubMenu &submenu) {
	AppendMenu(m_hMenu, MF_STRING | MF_POPUP, (UINT)*submenu.getHMENU(), submenu.m_lpNewItem);
}
void Menu::AddItem(int uIDNewItem, const char *lpNewItem) {
	AppendMenu(m_hMenu, MF_STRING, uIDNewItem, lpNewItem);
}


HMENU *Menu::getHMENU() {
	return &m_hMenu;
}

}