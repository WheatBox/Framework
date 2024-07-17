#include <FrameRender/Framebuffer.h>

#include <FrameAsset/Sprite.h>
#include <FrameCore/Globals.h>
#include <FrameCore/Camera.h>
#include <FrameRender/Renderer.h>

#include <glad/glad.h>

namespace Frame {

	CFramebuffer::CFramebuffer(const Frame::Vec2i & siz)
		: m_size { siz }
	{
		unsigned int texture = GenerateTexture(nullptr, 4, m_size, false);

		glGenFramebuffers(1, & m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		gRenderer->Clear(0x000000, 1.f);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_pImage = new SSpriteImage { texture, defaultUV_LT, defaultUV_RB, m_size, m_offset };
	}

	CFramebuffer::~CFramebuffer() {
		delete m_pImage;
		glDeleteFramebuffers(1, & m_FBO);
	}

	void CFramebuffer::Bind(bool bResetCamera, bool bClearAfterBind) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, m_size.x, m_size.y);
		
		if(bResetCamera) {
			m_bResetedCamera = true;

			m_viewSizeBefore = gCamera->GetViewSize();
			m_camZoomBefore = gCamera->GetZoom();
			m_camPosBefore = gCamera->GetPos();
			m_camRotationBefore = gCamera->GetRotation();

			gCamera->SetViewSize(m_size);
			gCamera->SetZoom(1.f);
			gCamera->SetPos(Vec2Cast(m_size) * .5f);
			gCamera->SetRotation(0.f);
		}

		if(bClearAfterBind) {
			gRenderer->Clear(0x000000, 0.f);
		}
	}

	void CFramebuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		const Vec2i windowSize = gCamera->GetWindowSize();
		glViewport(0, 0, windowSize.x, windowSize.y);

		if(m_bResetedCamera) {
			m_bResetedCamera = false;
			
			gCamera->SetViewSize(m_viewSizeBefore);
			gCamera->SetZoom(m_camZoomBefore);
			gCamera->SetPos(m_camPosBefore);
			gCamera->SetRotation(m_camRotationBefore);
		}
	}

}
