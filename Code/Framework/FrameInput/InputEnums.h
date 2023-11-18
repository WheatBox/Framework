#pragma once

#include <FrameUtility/BitOperation.h>

#include <SDL_keycode.h>

namespace Frame {

	// EInputState
	typedef Uint8 InputStateT;

	enum EInputState : InputStateT {
		eIS_Nothing = 0,
		eIS_Press   = FlagBit<Uint8>(0),
		eIS_Hold    = FlagBit<Uint8>(1),
		eIS_Release = FlagBit<Uint8>(2),
	};

	enum class EInputDevice {
		Keyboard,
	};

	enum EInputKeyId : int {

		eIKI_Unknown = SDLK_UNKNOWN,

		eIKI_Return = SDLK_RETURN,         // '\r'
		eIKI_Enter = SDLK_RETURN,          // '\r'
		eIKI_Escape = SDLK_ESCAPE,         // '\x1B'
		eIKI_Backspace = SDLK_BACKSPACE,   // '\b'
		eIKI_Tab = SDLK_TAB,               // '\t'
		eIKI_Space = SDLK_SPACE,           // ' '
		eIKI_Exclaim = SDLK_EXCLAIM,       // !
		eIKI_Quotedbl = SDLK_QUOTEDBL,     // "
		eIKI_Hash = SDLK_HASH,             // #
		eIKI_Percent = SDLK_PERCENT,       // %
		eIKI_Dollar = SDLK_DOLLAR,         // $
		eIKI_Ampersand = SDLK_AMPERSAND,   // &
		eIKI_Quote = SDLK_QUOTE,           // '\''
		eIKI_LeftParen = SDLK_LEFTPAREN,   // (
		eIKI_RightParen = SDLK_RIGHTPAREN, // )
		eIKI_Asterisk = SDLK_ASTERISK,     // *
		eIKI_Plus = SDLK_PLUS,             // +
		eIKI_Comma = SDLK_COMMA,           // ,
		eIKI_Minus = SDLK_MINUS,           // -
		eIKI_Period = SDLK_PERIOD,         // .
		eIKI_Slash = SDLK_SLASH,           // /

		eIKI_0 = SDLK_0,
		eIKI_1,
		eIKI_2,
		eIKI_3,
		eIKI_4,
		eIKI_5,
		eIKI_6,
		eIKI_7,
		eIKI_8,
		eIKI_9,

		eIKI_Colon      // :
			= SDLK_COLON,
		eIKI_Semicolon, // ;
		eIKI_Less,      // <
		eIKI_Equals,    // =
		eIKI_Greater,   // >
		eIKI_Question,  // ?
		eIKI_At,        // @

		eIKI_LeftBracket   // [
			= SDLK_LEFTBRACKET,
		eIKI_BackSlash,	   // '\\'
		eIKI_RightBracket, // ]
		eIKI_Caret,		   // ^
		eIKI_Underscore,   // _
		eIKI_BackQuote,	   // `

		eIKI_A = SDLK_a,
		eIKI_B,
		eIKI_C,
		eIKI_D,
		eIKI_E,
		eIKI_F,
		eIKI_G,
		eIKI_H,
		eIKI_I,
		eIKI_J,
		eIKI_K,
		eIKI_L,
		eIKI_M,
		eIKI_N,
		eIKI_O,
		eIKI_P,
		eIKI_Q,
		eIKI_R,
		eIKI_S,
		eIKI_T,
		eIKI_U,
		eIKI_V,
		eIKI_W,
		eIKI_X,
		eIKI_Y,
		eIKI_Z,

		eIKI_CapsLock = SDLK_CAPSLOCK,

		eIKI_F1 = SDLK_F1,
		eIKI_F2,
		eIKI_F3,
		eIKI_F4,
		eIKI_F5,
		eIKI_F6,
		eIKI_F7,
		eIKI_F8,
		eIKI_F9,
		eIKI_F10,
		eIKI_F11,
		eIKI_F12,

		eIKI_PrintScreen = SDLK_PRINTSCREEN,
		eIKI_ScrollLock = SDLK_SCROLLLOCK,
		eIKI_Pause = SDLK_PAUSE,
		eIKI_Insert = SDLK_INSERT,
		eIKI_Home = SDLK_HOME,
		eIKI_PageUp = SDLK_PAGEUP,
		eIKI_Delete = SDLK_DELETE,
		eIKI_End = SDLK_END,
		eIKI_PageDown = SDLK_PAGEDOWN,

		eIKI_Right = SDLK_RIGHT,
		eIKI_Left = SDLK_LEFT,
		eIKI_Down = SDLK_DOWN,
		eIKI_Up = SDLK_UP,

		eIKI_Numpad_NumLock = SDLK_NUMLOCKCLEAR,
		eIKI_Numpad_Divide = SDLK_KP_DIVIDE,
		eIKI_Numpad_Multiply = SDLK_KP_MULTIPLY,
		eIKI_Numpad_Minus = SDLK_KP_MINUS,
		eIKI_Numpad_Plus = SDLK_KP_PLUS,
		eIKI_Numpad_Enter = SDLK_KP_ENTER,

		eIKI_Numpad_1 = SDLK_KP_1,
		eIKI_Numpad_2,
		eIKI_Numpad_3,
		eIKI_Numpad_4,
		eIKI_Numpad_5,
		eIKI_Numpad_6,
		eIKI_Numpad_7,
		eIKI_Numpad_8,
		eIKI_Numpad_9,
		eIKI_Numpad_0,
		eIKI_Numpad_Period = SDLK_KP_PERIOD,

		eIKI_LCtrl = SDLK_LCTRL,
		eIKI_LShift = SDLK_LSHIFT,
		eIKI_LAlt = SDLK_LALT,

		eIKI_RCtrl = SDLK_RCTRL,
		eIKI_RShift = SDLK_RSHIFT,
		eIKI_RAlt = SDLK_RALT,

		eIKI_LGUI = SDLK_LGUI,
		eIKI_RGUI = SDLK_RGUI,
		eIKI_LWin = eIKI_LGUI,
		eIKI_RWin = eIKI_LGUI,
		eIKI_LCommand = eIKI_LGUI,
		eIKI_RCommand = eIKI_LGUI,

	};

}