#pragma once

#include <ZM/Window.hpp>

namespace zm {

class LIB_CLASS SubMenu {
public:
	SubMenu(const char *lpNewItem);

	void AddSubMenu(SubMenu &submenu);
	void AddItem(int uIDNewItem, const char *lpNewItem);

	HMENU *getHMENU();

	const char *m_lpNewItem;

private:
	HMENU m_hSubMenu;
};

}
