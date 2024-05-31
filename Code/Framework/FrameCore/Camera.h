#pragma once

#include <FrameMath/Vector2.h>

namespace Frame {

	class CShader;

	class CCamera final {

	public:

		Vec2 WindowToScene(const Vec2 & posOnWindow) const {
			Frame::Vec2 windowSize = Frame::Vec2Cast<float>(m_windowSize);
			Frame::Vec2 viewSize = Frame::Vec2Cast<float>(m_viewSize);
			return (posOnWindow - windowSize * .5f).Rotate(GetViewRotation()) * (viewSize / windowSize) / m_zoom + m_pos;
		}

		void __SetWindowSize(const Vec2i & siz) {
			m_windowSize = siz;
		}
		Vec2i GetWindowSize() const {
			return m_windowSize;
		}

		void SetViewSize(const Vec2i & siz) {
			m_viewSize = siz;
		}
		Vec2i GetViewSize() const {
			return m_viewSize;
		}

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

		// Radian
		void SetRotation(float angle) {
			m_rotation = angle;
		}
		// Radian
		float GetRotation() const {
			return m_rotation;
		}
		// Degree
		void SetRotationDegree(float angle) {
			m_rotation = DegToRad(angle);
		}
		// Degree
		float GetRotationDegree() const {
			return RadToDeg(m_rotation);
		}

		// Radian. View rotation = - Camera rotation
		void SetViewRotation(float angle) {
			m_rotation = -angle;
		}
		// Radian. View rotation = - Camera rotation
		float GetViewRotation() const {
			return -m_rotation;
		}
		// Degree. View rotation = - Camera rotation
		void SetViewRotationDegree(float angle) {
			m_rotation = -DegToRad(angle);
		}
		// Degree. View rotation = - Camera rotation
		float GetViewRotationDegree() const {
			return -RadToDeg(m_rotation);
		}

	private:
		Vec2i m_windowSize { 1 };
		Vec2i m_viewSize { 1 };
		Vec2 m_pos { 0.f }; // Center
		float m_zoom = 1.f;
		float m_rotation = 0.f; // Radian

	};

}