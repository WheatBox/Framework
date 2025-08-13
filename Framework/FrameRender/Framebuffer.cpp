#include "Framebuffer.h"

#include "../FrameAsset/Sprite.h"
#include "../FrameCore/Globals.h"
#include "../FrameCore/Camera.h"
#include "../FrameRender/Renderer.h"

#include <glad/glad.h>

#include <stack>

namespace Frame {

	CFramebuffer::CFramebuffer(const Frame::Vec2i & siz)
		: m_size { siz }
	{
		unsigned int texture = GenerateTexture(nullptr, 4, m_size, false);

		glGenFramebuffers(1, & m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		gRenderer->Clear(0x000000, 1.f, false);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_pImage = new SSpriteImage { texture, defaultUV_LT, defaultUV_RB, m_size, m_origin };
	}

	CFramebuffer::~CFramebuffer() {
		delete m_pImage;
		glDeleteFramebuffers(1, & m_FBO);
	}

	std::stack<unsigned int> __FBOStack;
	static void __FBOPush(unsigned int FBO) {
		gRenderer->GetRenderQueue()->Render();

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		__FBOStack.push(FBO);
	}
	static void __FBOPop() {
		gRenderer->GetRenderQueue()->Render();

		if(__FBOStack.empty()) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return;
		}
		__FBOStack.pop();
		if(__FBOStack.empty()) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		} else {
			glBindFramebuffer(GL_FRAMEBUFFER, __FBOStack.top());
		}
	}

	void CFramebuffer::Bind(bool bClearAfterBind) const {
		__FBOPush(m_FBO);
		gCamera->PushOntoStack();

		gCamera->SetViewport(0, m_size);
		gCamera->SetViewSize(m_size);
		gCamera->SetZoom(1.f);
		gCamera->SetPos(Vec2Cast(m_size) * .5f);
		gCamera->SetRotation(0.f);

		if(bClearAfterBind) {
			gRenderer->Clear(0x000000, 0.f);
		}
	}

	void CFramebuffer::Unbind() const {
		__FBOPop();
		gCamera->PopFromStack();
	}

}
