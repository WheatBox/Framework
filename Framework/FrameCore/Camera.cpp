#include "Camera.h"

#include <glad/glad.h>

namespace Frame {
	
	void CCamera::__SetWindowSize(const Vec2i & siz) {
		m_windowSize = siz;
		SetViewport(0, siz);
	}

	void CCamera::SetViewport(const Frame::Vec2i & pos, const Frame::Vec2i & siz) {
		m_data.viewportPos = pos;
		m_data.viewportSize = siz;
		glViewport(pos.x, pos.y, siz.x, siz.y);
	}

}
