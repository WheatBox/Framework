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
		eIKI_EnglishBase = SDLK_a,
		eIKI_A = eIKI_EnglishBase,
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
	};

}