#pragma once

#include <FrameMath/Vector2.h>

namespace Frame {

	struct SSpriteImage;
	
	class CFramebuffer {
	public:
		CFramebuffer() = delete;
		CFramebuffer(const Frame::Vec2i & siz);
		virtual ~CFramebuffer();

		static CFramebuffer * s_pCurrentBindingFramebuffer;
		static CFramebuffer * GetCurrentBindingFramebuffer() {
			return s_pCurrentBindingFramebuffer;
		}

		void Bind(bool bClearAfterBind = true);
		void Unbind();

		const SSpriteImage * GetImage() const {
			return m_pImage;
		}

		const Vec2i & GetSize() const {
			return m_size;
		}

	private:
		// 帧缓冲对象 (Framebuffer Object)
		unsigned int m_FBO = 0;

		SSpriteImage * m_pImage = nullptr;
		Vec2i m_size {};
		Vec2 m_offset {};
	};

}
