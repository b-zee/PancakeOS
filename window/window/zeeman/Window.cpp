#include <ZM/Window.hpp>

namespace zm {


ATOM Window::p_ClassAtom = 0;
HINSTANCE Window::m_hInstance = 0;

HKL Window::p_KeyboardLayout = GetKeyboardLayout(0);


Window::Window() :
	m_Open(false),
	p_window_title(0),
	m_Width(0),
	m_Height(0) {}
Window::Window(int width, int height, const char *app_name) :
	m_Open(false),
	p_window_title(app_name),
	m_Width(width),
	m_Height(height) {

	InitCommonControls();

	if (p_ClassAtom == 0) {
		_register_window_class();
	}

	_create_window();
}

bool Window::_register_window_class() {

	m_hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc;

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= 0;
	wc.lpfnWndProc		= &Window::_window_proc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= sizeof(Window *);
	wc.hInstance		= m_hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= CLASS_NAME;
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	p_ClassAtom = RegisterClassEx(&wc);

	if (p_ClassAtom == 0) {
		return false;
	}

	return true;

}
bool Window::_create_window() {

	m_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		CLASS_NAME, p_window_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
		NULL, NULL, m_hInstance, this);

	/*HWND hwndButton = CreateWindowEx( 
		0,
		"BUTTON", "OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10, 10, 64, 16,
		m_hWnd, NULL, m_hInstance, NULL);*/

	if (m_hWnd == NULL) {
		std::cout << GetLastError() << std::endl;
		return false;
	}


	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	m_Open = true;

	return true;
}

LRESULT CALLBACK Window::_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		void *lpCreateParam = create_struct->lpCreateParams;
		Window *this_window = reinterpret_cast<Window *>(lpCreateParam);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));

		this_window->setHWND(hWnd);

		return this_window->_process_event(uMsg, wParam, lParam);
	}

	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	Window *this_window = reinterpret_cast<Window *>(user_data);

	return this_window->_process_event(uMsg, wParam, lParam);

}

void Window::SetBitmap(HBITMAP bm) {
	m_hBitmap = bm;
}

void Window::draw(Jpeg *jpeg) {
	PAINTSTRUCT ps;
	HDC			hdc			= BeginPaint(m_hWnd, &ps);

	BITMAP		bitmap;
	HDC			hdcMem		= CreateCompatibleDC(hdc);
	HGDIOBJ		oldBitmap	= SelectObject(hdcMem, m_hBitmap);

	GetObject(m_hBitmap, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);

	EndPaint(m_hWnd, &ps);
}

LRESULT CALLBACK Window::_process_event(UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		case WM_CREATE: {
			Event event;
			event.type = Event::Create;
			_push_event(event);

			//m_hBitmap = (HBITMAP)LoadImage(m_hInstance, (LPCSTR)"lena.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		} case WM_PAINT: {
			Event event;
			event.type = Event::Paint;
			_push_event(event);

			//return DefWindowProc(m_hWnd, uMsg, wParam, lParam);

			PAINTSTRUCT ps;
			HDC			hdc			= BeginPaint(m_hWnd, &ps);

			BITMAP		bitmap;
			HDC			hdcMem		= CreateCompatibleDC(hdc);
			HGDIOBJ		oldBitmap	= SelectObject(hdcMem, m_hBitmap);

			GetObject(m_hBitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);

			EndPaint(m_hWnd, &ps);

			break;
		} case WM_DESTROY:
			break;
		case WM_CLOSE: {
			Event event;
			event.type = Event::Close;
			_push_event(event);

			break;
		} case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			Event event;
			event.type			= Event::Key;
			event.action		= Event::Down;
			/*event.key.alt		= HIWORD(GetAsyncKeyState(VK_MENU))		!= 0;
			event.key.control	= HIWORD(GetAsyncKeyState(VK_CONTROL))	!= 0;
			event.key.shift		= HIWORD(GetAsyncKeyState(VK_SHIFT))	!= 0;*/
			event.key.key		= static_cast<Keyboard::Key>(wParam);
			_push_event(event);

			break;
		} case WM_CHAR: {
			if (wParam != 27) {
				Event event;
				event.type			= Event::Key;
				event.action		= Event::Press;
				event.key.code		= wParam;
				_push_event(event);
			}

			break;
		} case WM_KEYUP:
		case WM_SYSKEYUP: {

			Event event;
			event.type			= Event::Key;
			event.action		= Event::Up;
			/*event.key.alt		= HIWORD(GetAsyncKeyState(VK_MENU))		!= 0;
			event.key.control	= HIWORD(GetAsyncKeyState(VK_CONTROL))	!= 0;
			event.key.shift		= HIWORD(GetAsyncKeyState(VK_SHIFT))	!= 0;*/
			event.key.key		= static_cast<Keyboard::Key>(wParam);
			_push_event(event);

			break;
		} case WM_COMMAND : {

			if (HIWORD(wParam) == 0) {
				Event event;
				event.type				= Event::Menu;
				event.menu.identifier	= LOWORD(wParam);
				_push_event(event);
			}

			break;
		}

		/*case WM_LBUTTONDBLCLK: {
			std::cout << "WM_LBUTTONDBLCLK" << std::endl;

			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Double;
			event.mouse.button	= Event::Left;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}*/
		case WM_LBUTTONDOWN: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Down;
			event.mouse.button	= Event::Left;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		} case WM_LBUTTONUP: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Up;
			event.mouse.button	= Event::Left;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}
		/*case WM_MBUTTONDBLCLK: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Double;
			event.mouse.button	= Event::Middle;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}*/
		case WM_MBUTTONDOWN: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Down;
			event.mouse.button	= Event::Middle;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		} case WM_MBUTTONUP: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Up;
			event.mouse.button	= Event::Middle;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}
		/*case WM_RBUTTONDBLCLK: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Double;
			event.mouse.button	= Event::Right;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}*/
		case WM_RBUTTONDOWN: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Down;
			event.mouse.button	= Event::Right;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		} case WM_RBUTTONUP: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Up;
			event.mouse.button	= Event::Right;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}
		/*case WM_XBUTTONDOWN: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Up;
			event.mouse.button	= GET_XBUTTON_WPARAM(wParam) == 1 ? Event::X1 : Event::X2;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		} case WM_XBUTTONUP: {
			Event event;
			event.type			= Event::Mouse;
			event.action		= Event::Up;
			event.mouse.button	= GET_XBUTTON_WPARAM(wParam) == 1 ? Event::X1 : Event::X2;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}*/
		case WM_MOUSEWHEEL: {
			Event event;
			event.type			= Event::Mouse;
			event.mouse.button	= Event::Wheel;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			event.mouse.direction= Event::Vertical;
			event.mouse.delta	= static_cast<int>(HIWORD(wParam)) / WHEEL_DELTA;
			_push_event(event);
			break;
		} case WM_MOUSEHWHEEL: {
			Event event;
			event.type			= Event::Mouse;
			event.mouse.button	= Event::Wheel;
			event.mouse.direction= Event::Horizontal;
			event.mouse.delta	= static_cast<int>(HIWORD(wParam)) / WHEEL_DELTA;
			_push_event(event);
			break;
		} case WM_MOUSELEAVE: {
			Event event;
			event.type			= Event::MouseLeave;
			_push_event(event);
			break;
		}
			break;
		case WM_MOUSEMOVE: {
			Event event;
			event.type			= Event::MouseMove;
			event.mouse.x		= GET_X_LPARAM(lParam);
			event.mouse.y		= GET_Y_LPARAM(lParam);
			_push_event(event);
			break;
		}
			break;
		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
bool Window::isOpen() {
	return m_Open;
}
void Window::close() {
	DestroyWindow(m_hWnd);

	m_Open = false;
}

bool Window::setMenuBar(MenuBar &menuBar) {
	SetMenu(m_hWnd, *menuBar.getHMENU());
}
void Window::setHWND(HWND hwnd) {
	m_hWnd = hwnd;
}

bool Window::_peek_events() {
	MSG Msg;

	while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
void Window::_push_event(Event event) {
	m_events.push(event);
}
bool Window::PopEvent(Event& event) {

	while (m_events.empty()) {
		_peek_events();
	}
	
	event = m_events.front();
	m_events.pop();

	return true;
}


void Window::setDimensions(int width, int height) {
	m_Width = width;
	m_Height = height;

	//LPRECT lpRect;
	//GetWindowRect(m_hWnd, lpRect);



	SetWindowPos(
		m_hWnd,0,
		//lpRect.left, lpRect.top,
		0,0,
		width, height,
		SWP_NOMOVE | SWP_NOOWNERZORDER);
}

}