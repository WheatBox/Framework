#pragma once

#include <FrameMath/Vector2.h>

namespace Frame {

	struct SSpriteImage;
	
	class CFramebuffer {
	public:
		CFramebuffer() = delete;
		CFramebuffer(const Frame::Vec2i & siz);
		virtual ~CFramebuffer();

		// 若 bResetCamera 被设为 true，在后续调用 Unbind() 时摄像机会被改回 Bind() 之前的状态
		// If bResetCamera is set to true, the camera will be changed back to the state before Bind() when calling Unbind() in the future
		void Bind(bool bResetCamera, bool bClearAfterBind);
		void Bind() {
			Bind(true, true);
		}
		void Unbind();

		const SSpriteImage * GetImage() const {
			return m_pImage;
		}

		const Vec2i & GetSize() const {
			return m_size;
		}

	private:
		bool m_bResetedCamera = false;
		Vec2i m_viewSizeBefore {};
		float m_camZoomBefore = 0.f;
		Frame::Vec2 m_camPosBefore {};
		float m_camRotationBefore = 0.f;

		// 帧缓冲对象 (Framebuffer Object)
		unsigned int m_FBO = 0;

		SSpriteImage * m_pImage = nullptr;
		Vec2i m_size {};
		Vec2 m_offset {};
	};

}
