#include <ZM/Menu.hpp>

namespace zm {

MenuBar::MenuBar() {
	m_hMenuBar = CreateMenu();
}

void MenuBar::AddMenu(Menu &menu) {
	AppendMenu(m_hMenuBar, MF_STRING | MF_POPUP, (UINT)*menu.getHMENU(), menu.m_lpNewItem);
}

HMENU *MenuBar::getHMENU() {
	return &m_hMenuBar;
}

}