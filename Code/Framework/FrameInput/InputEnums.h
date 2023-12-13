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

	enum EInputKeyId : int {

		/* The unknown key */
		eIKI_Unknown = -1, // GLFW_KEY_UNKNOWN

		/* Printable keys */
		eIKI_Space = 32, // GLFW_KEY_SPACE
		eIKI_Quote = 39, // ' // GLFW_KEY_APOSTROPHE
		eIKI_Comma = 44, // , // GLFW_KEY_COMMA
		eIKI_Subtract = 45, // - // GLFW_KEY_MINUS
		eIKI_Period = 46, // . // GLFW_KEY_PERIOD
		eIKI_Slash = 47, // / //GLFW_KEY_SLASH
		eIKI_0 = 48, // GLFW_KEY_0
		eIKI_1 = 49, // GLFW_KEY_1
		eIKI_2 = 50, // GLFW_KEY_2
		eIKI_3 = 51, // GLFW_KEY_3
		eIKI_4 = 52, // GLFW_KEY_4
		eIKI_5 = 53, // GLFW_KEY_5
		eIKI_6 = 54, // GLFW_KEY_6
		eIKI_7 = 55, // GLFW_KEY_7
		eIKI_8 = 56, // GLFW_KEY_8
		eIKI_9 = 57, // GLFW_KEY_9
		eIKI_Semicolon = 59, // ; // GLFW_KEY_SEMICOLON
		eIKI_Equal = 61, // = // GLFW_KEY_EQUAL
		eIKI_A = 65, // GLFW_KEY_A
		eIKI_B = 66, // GLFW_KEY_B
		eIKI_C = 67, // GLFW_KEY_C
		eIKI_D = 68, // GLFW_KEY_D
		eIKI_E = 69, // GLFW_KEY_E
		eIKI_F = 70, // GLFW_KEY_F
		eIKI_G = 71, // GLFW_KEY_G
		eIKI_H = 72, // GLFW_KEY_H
		eIKI_I = 73, // GLFW_KEY_I
		eIKI_J = 74, // GLFW_KEY_J
		eIKI_K = 75, // GLFW_KEY_K
		eIKI_L = 76, // GLFW_KEY_L
		eIKI_M = 77, // GLFW_KEY_M
		eIKI_N = 78, // GLFW_KEY_N
		eIKI_O = 79, // GLFW_KEY_O
		eIKI_P = 80, // GLFW_KEY_P
		eIKI_Q = 81, // GLFW_KEY_Q
		eIKI_R = 82, // GLFW_KEY_R
		eIKI_S = 83, // GLFW_KEY_S
		eIKI_T = 84, // GLFW_KEY_T
		eIKI_U = 85, // GLFW_KEY_U
		eIKI_V = 86, // GLFW_KEY_V
		eIKI_W = 87, // GLFW_KEY_W
		eIKI_X = 88, // GLFW_KEY_X
		eIKI_Y = 89, // GLFW_KEY_Y
		eIKI_Z = 90, // GLFW_KEY_Z
		eIKI_LeftBracket = 91, // [ // GLFW_KEY_LEFT_BRACKET
		eIKI_BackSlash = 92, // \ // GLFW_KEY_BACKSLASH
		eIKI_RightBracket = 93, // ] // GLFW_KEY_RIGHT_BRACKET
		eIKI_BackQuote = 96, // ` // GLFW_KEY_GRAVE_ACCENT
		eIKI_World1_161, // GLFW_KEY_WORLD_1 /* non-US #1 */
		eIKI_World2_162, // GLFW_KEY_WORLD_2 /* non-US #2 */

		/* Function keys */
		eIKI_Escape = 256, // GLFW_KEY_ESCAPE
		eIKI_Enter = 257, // GLFW_KEY_ENTER
		eIKI_Tab = 258, // GLFW_KEY_TAB
		eIKI_Backspace = 259, // GLFW_KEY_BACKSPACE
		eIKI_Insert = 260, // GLFW_KEY_INSERT
		eIKI_Delete = 261, // GLFW_KEY_DELETE
		eIKI_Right = 262, // GLFW_KEY_RIGHT
		eIKI_Left = 263, // GLFW_KEY_LEFT
		eIKI_Down = 264, // GLFW_KEY_DOWN
		eIKI_Up = 265, // GLFW_KEY_UP
		eIKI_PageUp = 266, // GLFW_KEY_PAGE_UP
		eIKI_PageDown = 267, // GLFW_KEY_PAGE_DOWN
		eIKI_Home = 268, // GLFW_KEY_HOME
		eIKI_End = 269, // GLFW_KEY_END
		eIKI_CapsLock = 280, // GLFW_KEY_CAPS_LOCK
		eIKI_ScrollLock = 281, // GLFW_KEY_SCROLL_LOCK
		eIKI_Numpad_NumLock = 282, // GLFW_KEY_NUM_LOCK
		eIKI_PrintScreen = 283, // GLFW_KEY_PRINT_SCREEN
		eIKI_Pause = 284, // GLFW_KEY_PAUSE
		eIKI_F1 = 290, // GLFW_KEY_F1
		eIKI_F2 = 291, // GLFW_KEY_F2
		eIKI_F3 = 292, // GLFW_KEY_F3
		eIKI_F4 = 293, // GLFW_KEY_F4
		eIKI_F5 = 294, // GLFW_KEY_F5
		eIKI_F6 = 295, // GLFW_KEY_F6
		eIKI_F7 = 296, // GLFW_KEY_F7
		eIKI_F8 = 297, // GLFW_KEY_F8
		eIKI_F9 = 298, // GLFW_KEY_F9
		eIKI_F10 = 299, // GLFW_KEY_F10
		eIKI_F11 = 300, // GLFW_KEY_F11
		eIKI_F12 = 301, // GLFW_KEY_F12
		eIKI_F13 = 302, // GLFW_KEY_F13
		eIKI_F14 = 303, // GLFW_KEY_F14
		eIKI_F15 = 304, // GLFW_KEY_F15
		eIKI_F16 = 305, // GLFW_KEY_F16
		eIKI_F17 = 306, // GLFW_KEY_F17
		eIKI_F18 = 307, // GLFW_KEY_F18
		eIKI_F19 = 308, // GLFW_KEY_F19
		eIKI_F20 = 309, // GLFW_KEY_F20
		eIKI_F21 = 310, // GLFW_KEY_F21
		eIKI_F22 = 311, // GLFW_KEY_F22
		eIKI_F23 = 312, // GLFW_KEY_F23
		eIKI_F24 = 313, // GLFW_KEY_F24
		eIKI_F25 = 314, // GLFW_KEY_F25
		eIKI_Numpad_0 = 320, // GLFW_KEY_KP_0
		eIKI_Numpad_1 = 321, // GLFW_KEY_KP_1
		eIKI_Numpad_2 = 322, // GLFW_KEY_KP_2
		eIKI_Numpad_3 = 323, // GLFW_KEY_KP_3
		eIKI_Numpad_4 = 324, // GLFW_KEY_KP_4
		eIKI_Numpad_5 = 325, // GLFW_KEY_KP_5
		eIKI_Numpad_6 = 326, // GLFW_KEY_KP_6
		eIKI_Numpad_7 = 327, // GLFW_KEY_KP_7
		eIKI_Numpad_8 = 328, // GLFW_KEY_KP_8
		eIKI_Numpad_9 = 329, // GLFW_KEY_KP_9
		eIKI_Numpad_Period = 330, // GLFW_KEY_KP_DECIMAL
		eIKI_Numpad_Divide = 331, // GLFW_KEY_KP_DIVIDE
		eIKI_Numpad_Multiply = 332, // GLFW_KEY_KP_MULTIPLY
		eIKI_Numpad_Subtract = 333, // GLFW_KEY_KP_SUBTRACT
		eIKI_Numpad_Add = 334, // GLFW_KEY_KP_ADD
		eIKI_Numpad_Enter = 335, // GLFW_KEY_KP_ENTER
		eIKI_Numpad_Equal = 336, // GLFW_KEY_KP_EQUAL
		eIKI_LShift = 340, // GLFW_KEY_LEFT_SHIFT
		eIKI_LCtrl = 341, // GLFW_KEY_LEFT_CONTROL
		eIKI_LAlt = 342, // GLFW_KEY_LEFT_ALT
		eIKI_LSuper = 343, // GLFW_KEY_LEFT_SUPER
		eIKI_RShift = 344, // GLFW_KEY_RIGHT_SHIFT
		eIKI_RCtrl = 345, // GLFW_KEY_RIGHT_CONTROL
		eIKI_RAlt = 346, // GLFW_KEY_RIGHT_ALT
		eIKI_RSuper = 347, // GLFW_KEY_RIGHT_SUPER
		eIKI_Menu = 348, // GLFW_KEY_MENU

	};

}