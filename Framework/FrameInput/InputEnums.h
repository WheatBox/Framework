#pragma once

#include <FrameUtility/BitOperation.h>

namespace Frame {

	// EInputState
	typedef uint8 InputStateT;

	enum EInputState : InputStateT {
		eIS_Nothing = 0,
		eIS_Press   = FlagBit<uint8>(0),
		eIS_Hold    = FlagBit<uint8>(1),
		eIS_Release = FlagBit<uint8>(2),
	};

	enum class EInputDevice {
		Keyboard,
	};

	enum EKeyId : int {

		/* The unknown key */
		eKI_Unknown = -1, // GLFW_KEY_UNKNOWN

		/* Printable keys */
		eKI_Space = 32, // GLFW_KEY_SPACE
		eKI_Quote = 39, // ' // GLFW_KEY_APOSTROPHE
		eKI_Comma = 44, // , // GLFW_KEY_COMMA
		eKI_Subtract = 45, // - // GLFW_KEY_MINUS
		eKI_Period = 46, // . // GLFW_KEY_PERIOD
		eKI_Slash = 47, // / //GLFW_KEY_SLASH
		eKI_0 = 48, // GLFW_KEY_0
		eKI_1 = 49, // GLFW_KEY_1
		eKI_2 = 50, // GLFW_KEY_2
		eKI_3 = 51, // GLFW_KEY_3
		eKI_4 = 52, // GLFW_KEY_4
		eKI_5 = 53, // GLFW_KEY_5
		eKI_6 = 54, // GLFW_KEY_6
		eKI_7 = 55, // GLFW_KEY_7
		eKI_8 = 56, // GLFW_KEY_8
		eKI_9 = 57, // GLFW_KEY_9
		eKI_Semicolon = 59, // ; // GLFW_KEY_SEMICOLON
		eKI_Equal = 61, // = // GLFW_KEY_EQUAL
		eKI_A = 65, // GLFW_KEY_A
		eKI_B = 66, // GLFW_KEY_B
		eKI_C = 67, // GLFW_KEY_C
		eKI_D = 68, // GLFW_KEY_D
		eKI_E = 69, // GLFW_KEY_E
		eKI_F = 70, // GLFW_KEY_F
		eKI_G = 71, // GLFW_KEY_G
		eKI_H = 72, // GLFW_KEY_H
		eKI_I = 73, // GLFW_KEY_I
		eKI_J = 74, // GLFW_KEY_J
		eKI_K = 75, // GLFW_KEY_K
		eKI_L = 76, // GLFW_KEY_L
		eKI_M = 77, // GLFW_KEY_M
		eKI_N = 78, // GLFW_KEY_N
		eKI_O = 79, // GLFW_KEY_O
		eKI_P = 80, // GLFW_KEY_P
		eKI_Q = 81, // GLFW_KEY_Q
		eKI_R = 82, // GLFW_KEY_R
		eKI_S = 83, // GLFW_KEY_S
		eKI_T = 84, // GLFW_KEY_T
		eKI_U = 85, // GLFW_KEY_U
		eKI_V = 86, // GLFW_KEY_V
		eKI_W = 87, // GLFW_KEY_W
		eKI_X = 88, // GLFW_KEY_X
		eKI_Y = 89, // GLFW_KEY_Y
		eKI_Z = 90, // GLFW_KEY_Z
		eKI_LeftBracket = 91, // [ // GLFW_KEY_LEFT_BRACKET
		eKI_BackSlash = 92, // \ // GLFW_KEY_BACKSLASH
		eKI_RightBracket = 93, // ] // GLFW_KEY_RIGHT_BRACKET
		eKI_BackQuote = 96, // ` // GLFW_KEY_GRAVE_ACCENT
		eKI_World1_161, // GLFW_KEY_WORLD_1 /* non-US #1 */
		eKI_World2_162, // GLFW_KEY_WORLD_2 /* non-US #2 */

		/* Function keys */
		eKI_Escape = 256, // GLFW_KEY_ESCAPE
		eKI_Enter = 257, // GLFW_KEY_ENTER
		eKI_Tab = 258, // GLFW_KEY_TAB
		eKI_Backspace = 259, // GLFW_KEY_BACKSPACE
		eKI_Insert = 260, // GLFW_KEY_INSERT
		eKI_Delete = 261, // GLFW_KEY_DELETE
		eKI_Right = 262, // GLFW_KEY_RIGHT
		eKI_Left = 263, // GLFW_KEY_LEFT
		eKI_Down = 264, // GLFW_KEY_DOWN
		eKI_Up = 265, // GLFW_KEY_UP
		eKI_PageUp = 266, // GLFW_KEY_PAGE_UP
		eKI_PageDown = 267, // GLFW_KEY_PAGE_DOWN
		eKI_Home = 268, // GLFW_KEY_HOME
		eKI_End = 269, // GLFW_KEY_END
		eKI_CapsLock = 280, // GLFW_KEY_CAPS_LOCK
		eKI_ScrollLock = 281, // GLFW_KEY_SCROLL_LOCK
		eKI_Numpad_NumLock = 282, // GLFW_KEY_NUM_LOCK
		eKI_PrintScreen = 283, // GLFW_KEY_PRINT_SCREEN
		eKI_Pause = 284, // GLFW_KEY_PAUSE
		eKI_F1 = 290, // GLFW_KEY_F1
		eKI_F2 = 291, // GLFW_KEY_F2
		eKI_F3 = 292, // GLFW_KEY_F3
		eKI_F4 = 293, // GLFW_KEY_F4
		eKI_F5 = 294, // GLFW_KEY_F5
		eKI_F6 = 295, // GLFW_KEY_F6
		eKI_F7 = 296, // GLFW_KEY_F7
		eKI_F8 = 297, // GLFW_KEY_F8
		eKI_F9 = 298, // GLFW_KEY_F9
		eKI_F10 = 299, // GLFW_KEY_F10
		eKI_F11 = 300, // GLFW_KEY_F11
		eKI_F12 = 301, // GLFW_KEY_F12
		eKI_F13 = 302, // GLFW_KEY_F13
		eKI_F14 = 303, // GLFW_KEY_F14
		eKI_F15 = 304, // GLFW_KEY_F15
		eKI_F16 = 305, // GLFW_KEY_F16
		eKI_F17 = 306, // GLFW_KEY_F17
		eKI_F18 = 307, // GLFW_KEY_F18
		eKI_F19 = 308, // GLFW_KEY_F19
		eKI_F20 = 309, // GLFW_KEY_F20
		eKI_F21 = 310, // GLFW_KEY_F21
		eKI_F22 = 311, // GLFW_KEY_F22
		eKI_F23 = 312, // GLFW_KEY_F23
		eKI_F24 = 313, // GLFW_KEY_F24
		eKI_F25 = 314, // GLFW_KEY_F25
		eKI_Numpad_0 = 320, // GLFW_KEY_KP_0
		eKI_Numpad_1 = 321, // GLFW_KEY_KP_1
		eKI_Numpad_2 = 322, // GLFW_KEY_KP_2
		eKI_Numpad_3 = 323, // GLFW_KEY_KP_3
		eKI_Numpad_4 = 324, // GLFW_KEY_KP_4
		eKI_Numpad_5 = 325, // GLFW_KEY_KP_5
		eKI_Numpad_6 = 326, // GLFW_KEY_KP_6
		eKI_Numpad_7 = 327, // GLFW_KEY_KP_7
		eKI_Numpad_8 = 328, // GLFW_KEY_KP_8
		eKI_Numpad_9 = 329, // GLFW_KEY_KP_9
		eKI_Numpad_Period = 330, // GLFW_KEY_KP_DECIMAL
		eKI_Numpad_Divide = 331, // GLFW_KEY_KP_DIVIDE
		eKI_Numpad_Multiply = 332, // GLFW_KEY_KP_MULTIPLY
		eKI_Numpad_Subtract = 333, // GLFW_KEY_KP_SUBTRACT
		eKI_Numpad_Add = 334, // GLFW_KEY_KP_ADD
		eKI_Numpad_Enter = 335, // GLFW_KEY_KP_ENTER
		eKI_Numpad_Equal = 336, // GLFW_KEY_KP_EQUAL
		eKI_LShift = 340, // GLFW_KEY_LEFT_SHIFT
		eKI_LCtrl = 341, // GLFW_KEY_LEFT_CONTROL
		eKI_LAlt = 342, // GLFW_KEY_LEFT_ALT
		eKI_LSuper = 343, // GLFW_KEY_LEFT_SUPER
		eKI_RShift = 344, // GLFW_KEY_RIGHT_SHIFT
		eKI_RCtrl = 345, // GLFW_KEY_RIGHT_CONTROL
		eKI_RAlt = 346, // GLFW_KEY_RIGHT_ALT
		eKI_RSuper = 347, // GLFW_KEY_RIGHT_SUPER
		eKI_Menu = 348, // GLFW_KEY_MENU

	};

	enum EMouseButtonId : int {
		eMBI_1 = 0, // GLFW_MOUSE_BUTTON_1
		eMBI_2 = 1, // GLFW_MOUSE_BUTTON_2
		eMBI_3 = 2, // GLFW_MOUSE_BUTTON_3
		eMBI_4 = 3, // GLFW_MOUSE_BUTTON_4
		eMBI_5 = 4, // GLFW_MOUSE_BUTTON_5
		eMBI_6 = 5, // GLFW_MOUSE_BUTTON_6
		eMBI_7 = 6, // GLFW_MOUSE_BUTTON_7
		eMBI_8 = 7, // GLFW_MOUSE_BUTTON_8
		eMBI_Last = eMBI_8, // GLFW_MOUSE_BUTTON_LAST
		eMBI_Left = eMBI_1, // GLFW_MOUSE_BUTTON_LEFT
		eMBI_Right = eMBI_2, // GLFW_MOUSE_BUTTON_RIGHT
		eMBI_Middle = eMBI_3, // GLFW_MOUSE_BUTTON_MIDDLE
	};

}