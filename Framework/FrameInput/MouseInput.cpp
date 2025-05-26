#include "MouseInput.h"

#include "../FrameCore/Globals.h"
#include "../FrameCore/Camera.h"

#include <GLFW/glfw3.h>

namespace Frame {

	void CMouseInput::SetPosition(const Vec2 & vPos) {
		glfwSetCursorPos(m_pWindow, static_cast<float>(vPos.x), static_cast<float>(vPos.y));
		m_vPos = vPos;
	}

	Vec2 CMouseInput::GetPositionInScene() const {
		return Frame::gCamera->WindowToScene(m_vPos);
	}

}