#include <FrameInput/MouseInput.h>

#include <GLFW/glfw3.h>

namespace Frame {

	void CMouseInput::SetPosition(const Vec2 & vPos) {
		glfwSetCursorPos(m_pWindow, static_cast<float>(vPos.x), static_cast<float>(vPos.y));
		m_vPos = vPos;
	}

}