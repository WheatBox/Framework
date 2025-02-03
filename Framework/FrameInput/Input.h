#pragma once

#include <FrameInput/KeyboardInput.h>
#include <FrameInput/MouseInput.h>

struct GLFWwindow;

namespace Frame {

	class CInput {
	private:
		GLFWwindow * m_pWindow = nullptr;
	public:
		CInput()
			: pKeyboard { new CKeyboardInput {} }
			, pMouse { new CMouseInput {} }
		{}
		virtual ~CInput() {
			delete pKeyboard;
			delete pMouse;
		}

		void Initialize(GLFWwindow * pWindow);

		void Process() {
			pKeyboard->__ProcessChanges();
			pMouse->__ProcessChanges();
		}

		CKeyboardInput * const pKeyboard;
		CMouseInput * const pMouse;
	};

}