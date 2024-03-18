#pragma once

#include <FrameMath/Vector2.h>

namespace Frame {

	class CShader;

	class CCamera final {

	public:
		// Center
		void SetPos(const Vec2 & pos) {
			m_pos = pos;
		}
		// Center
		Vec2 GetPos() const {
			return m_pos;
		}

		void SetZoom(float zoom) {
			m_zoom = zoom;
		}
		float GetZoom() const {
			return m_zoom;
		}

	private:
		Vec2 m_pos { 0.f }; // Center
		float m_zoom = 1.f;

	};

}