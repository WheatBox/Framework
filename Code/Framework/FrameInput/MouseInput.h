#pragma once

#include <FrameInput/ButtonInputBase.h>
#include <FrameMath/Vector2.h>

struct GLFWwindow;

namespace Frame {

	class CMouseInput : public CButtonInputBase<EMouseButtonId> {

	public:
		void Initialize(GLFWwindow * pWindow) {
			m_pWindow = pWindow;
		}

		void __PosCallback(double xpos, double ypos) {
			m_vPos = { static_cast<float>(xpos), static_cast<float>(ypos) };
		}

		void SetPosition(const Vec2 & vPos);
		const Vec2 & GetPosition() const {
			return m_vPos;
		}

		// TODO - 滚轮

	private:
		GLFWwindow * m_pWindow = nullptr;
		Vec2 m_vPos {};
	};

}