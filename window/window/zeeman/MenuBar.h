#pragma once

#include <ZM/Window.hpp>

namespace zm {

class LIB_CLASS MenuBar {
public:
	MenuBar();

	void AddMenu(Menu &menu);

	HMENU *getHMENU();

private:
	HMENU m_hMenuBar;
};

}
