#pragma once

namespace zm {

class LIB_CLASS Event {
public:
	enum EventType {
		Create,
		Close,
		Paint,
		Menu,
		Key,
		Mouse,
		MouseLeave,
		MouseMove
	} type;

	enum EventAction {
		Down,
		Press,
		Up,
		Double
	} action;

	enum MouseButton {
		Left,
		Middle,
		Right,
		Wheel
	};
	enum MouseDirection {
		Horizontal,
		Vertical
	};

	struct KeyEvent
	{
		Keyboard::Key	key;
		char			code;
	} key;

	struct Mouse
	{
		MouseButton		button;
		MouseDirection	direction;
		int				delta;
		int				x;
		int				y;
	} mouse;

	struct Menu
	{
		int identifier;
	} menu;
};

}
