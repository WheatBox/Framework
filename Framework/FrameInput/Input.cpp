#include <FrameInput/Input.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Frame {

	CKeyboardInput * __pKeyboard;
	CMouseInput * __pMouse;

	void CInput::Initialize(GLFWwindow * pWindow) {
		m_pWindow = pWindow;
		pMouse->Initialize(pWindow);
		
		__pKeyboard = pKeyboard;
		glfwSetKeyCallback(m_pWindow, [](GLFWwindow *, int key, int, int action, int) -> void {
			__pKeyboard->__ButtonCallback(key, action);
		});

		__pMouse = pMouse;
		glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow *, double xpos, double ypos) -> void {
			__pMouse->__PosCallback(xpos, ypos);
		});
		glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow *, int button, int action, int) -> void {
			__pMouse->__ButtonCallback(button, action);
		});
		glfwSetScrollCallback(m_pWindow, [](GLFWwindow *, double xpos, double ypos) -> void {
			__pMouse->__ScrollCallback(xpos, ypos);
		});
	}

}