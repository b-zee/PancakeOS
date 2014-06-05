#pragma once

#include "Window.hpp"

namespace zm {

class LIB_CLASS Menu {
public:
	Menu(const char *lpNewItem);

	void AddSubMenu(SubMenu &submenu);
	void AddItem(int uIDNewItem, const char *lpNewItem);

	HMENU *getHMENU();

	const char *m_lpNewItem;

private:
	HMENU m_hMenu;
};

}
