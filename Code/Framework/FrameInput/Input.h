#pragma once

#include <FrameInput/KeyboardInput.h>

struct GLFWwindow;

namespace Frame {

	class CInput {
	private:
		GLFWwindow * m_pWindow = nullptr;
	public:
		CInput() {
			pKeyboard = new CKeyboardInput {};
		}

		void Initialize(GLFWwindow * pWindow);

		void Process() {
			pKeyboard->ProcessChanges();
		}

		CKeyboardInput * pKeyboard;
	};

}