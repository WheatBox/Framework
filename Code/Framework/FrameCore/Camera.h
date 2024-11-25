#pragma once

#include <FrameMath/Vector2.h>

#include <stack>

namespace Frame {

	class CShader;

	class CCamera final {

	public:

		Vec2 WindowToScene(const Vec2 & posOnWindow) const {
			Frame::Vec2 windowSize = Frame::Vec2Cast<float>(m_windowSize);
			Frame::Vec2 viewSize = Frame::Vec2Cast<float>(m_data.viewSize);
			return (posOnWindow - windowSize * .5f).GetRotated(GetViewRotation()) * (viewSize / windowSize) / m_data.zoom + m_data.pos;
		}

		void __SetWindowSize(const Vec2i & siz);
		const Vec2i & GetWindowSize() const {
			return m_windowSize;
		}

		void SetViewport(const Vec2i & pos, const Vec2i & siz);
		void SetViewportPos(const Vec2i & pos) {
			SetViewport(pos, m_data.viewportSize);
		}
		void SetViewportSize(const Vec2i & siz) {
			SetViewport(m_data.viewportPos, siz);
		}
		const Vec2i & GetViewPortPos() const {
			return m_data.viewportPos;
		}
		const Vec2i & GetViewPortSize() const {
			return m_data.viewportSize;
		}

		void SetViewSize(const Vec2i & siz) {
			m_data.viewSize = siz;
		}
		const Vec2i & GetViewSize() const {
			return m_data.viewSize;
		}

		// Center
		void SetPos(const Vec2 & pos) {
			m_data.pos = pos;
		}
		// Center
		const Vec2 & GetPos() const {
			return m_data.pos;
		}

		void SetZoom(float zoom) {
			m_data.zoom = zoom;
		}
		float GetZoom() const {
			return m_data.zoom;
		}

		// Radian
		void SetRotation(float angle) {
			m_data.rotation = angle;
		}
		// Radian
		float GetRotation() const {
			return m_data.rotation;
		}
		// Degree
		void SetRotationDegree(float angle) {
			m_data.rotation = DegToRad(angle);
		}
		// Degree
		float GetRotationDegree() const {
			return RadToDeg(m_data.rotation);
		}

		// Radian. View rotation = - Camera rotation
		void SetViewRotation(float angle) {
			m_data.rotation = -angle;
		}
		// Radian. View rotation = - Camera rotation
		float GetViewRotation() const {
			return -m_data.rotation;
		}
		// Degree. View rotation = - Camera rotation
		void SetViewRotationDegree(float angle) {
			m_data.rotation = -DegToRad(angle);
		}
		// Degree. View rotation = - Camera rotation
		float GetViewRotationDegree() const {
			return -RadToDeg(m_data.rotation);
		}

		void PushOntoStack() {
			m_stack.push(m_data);
		}
		void PopFromStack() {
			if(m_stack.empty()) {
				return;
			}
			m_data = m_stack.top();
			SetViewport(m_data.viewportPos, m_data.viewportSize);
			m_stack.pop();
		}

	private:
		Vec2i m_windowSize { 1 };

		struct __SMyData {
			Vec2i viewportPos { 0 };  // glViewPort
			Vec2i viewportSize { 1 }; //
			Vec2i viewSize { 1 };
			Vec2 pos { 0.f }; // Center
			float zoom = 1.f;
			float rotation = 0.f; // Radian
		} m_data;

		std::stack<__SMyData> m_stack;
	};

}