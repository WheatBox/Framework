#pragma once

#include <FrameInput/KeyboardInput.h>

namespace Frame {

	class CInputManager {
	public:
		CInputManager() {
			pKeyboard = new CKeyboardInput {};
		}

		CKeyboardInput * pKeyboard;
	};

}