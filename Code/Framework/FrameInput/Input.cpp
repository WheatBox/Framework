#include <FrameInput/Input.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Frame {

	CKeyboardInput * __pKeyboard;

	void CInput::Initialize(GLFWwindow * pWindow) {
		__pKeyboard = pKeyboard;
		m_pWindow = pWindow;
		glfwSetKeyCallback(m_pWindow, [](GLFWwindow *, int key, int, int action, int) -> void {
			switch(action) {
			case GLFW_RELEASE:
				__pKeyboard->SetInputState(static_cast<EInputKeyId>(key), EInputState::eIS_Release);
				break;
			case GLFW_PRESS:
				__pKeyboard->SetInputState(static_cast<EInputKeyId>(key), EInputState::eIS_Press);
				break;
			}
		});
	}

}