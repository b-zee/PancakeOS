#include <ZM/Menu.hpp>

namespace zm {

SubMenu::SubMenu(const char *lpNewItem) : m_lpNewItem(lpNewItem) {
	m_hSubMenu = CreatePopupMenu();
}
void SubMenu::AddSubMenu(SubMenu &submenu) {
	AppendMenu(m_hSubMenu, MF_STRING | MF_POPUP, (UINT)*submenu.getHMENU(), submenu.m_lpNewItem);
}
void SubMenu::AddItem(int uIDNewItem, const char *lpNewItem) {
	AppendMenu(m_hSubMenu, MF_STRING, uIDNewItem, lpNewItem);
}


HMENU *SubMenu::getHMENU() {
	return &m_hSubMenu;
}

}