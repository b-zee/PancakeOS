#pragma once

#ifdef __WIN32__
#ifdef BUILD_LIB
#define LIB_CLASS __declspec(dllexport)
#else
#define LIB_CLASS __declspec(dllimport)
#endif
#else
#define LIB_CLASS
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <string>
#include <iostream>
#include <queue>


#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL                  0x020E
#endif


class LIB_CLASS SubMenu;
class LIB_CLASS Menu;
class LIB_CLASS MenuBar;
class LIB_CLASS Jpeg;

#include <ZM/Keyboard.hpp>
#include <ZM/Event.hpp>
#include <ZM/Menu.hpp>
#include <ZM/Jpeg.hpp>

#define CLASS_NAME "henkie"

namespace zm {

class LIB_CLASS Window {
public:
	Window();
	Window(int width, int height, const char *app_name);

	bool PopEvent(Event &event);

	bool isOpen();
	void close();

	bool setMenuBar(MenuBar &menubar);

	void setDimensions(int width, int height);

	void SetBitmap(HBITMAP bm);

	void draw(Jpeg *jpeg);

private:
	void setHWND(HWND hwnd);
	HWND		m_hWnd;
	static ATOM	p_ClassAtom;
	const char	*p_window_title;

	static HKL	p_KeyboardLayout;

	bool		m_Open;

	HBITMAP m_hBitmap;


	int		m_Width, m_Height;

	std::queue<Event> m_events;

	static HINSTANCE m_hInstance;
	bool _register_window_class();
	bool _create_window();
	bool _peek_events();

	void _push_event(Event event);

	static LRESULT CALLBACK _window_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK _process_event(UINT msg, WPARAM wParam, LPARAM lParam);
};


}
