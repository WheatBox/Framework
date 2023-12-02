#include <FrameRender/TextRenderer.h>

#include <FrameRender/DefaultShaders.h>
#include <FrameRender/Renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	CTextRenderer::CTextRenderer(CRenderer * pRenderer)
		: m_pRenderer { pRenderer }
		, m_color { pRenderer->GetColor() }
		, m_alpha { pRenderer->GetAlpha() }
		, m_pDefaultShader { new CShader {} }
	{
		glGenBuffers(1, & m_VBO);
		glGenVertexArrays(1, & m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		GLsizei stride = (3 + 2) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		if(!m_pDefaultShader->CompileFiles(DEFAULT_TEXT_SHADER_FILES)) {
			// TODO - 警告信息
			m_pDefaultShader->Compile(DEFAULT_TEXT_SHADER);
		}
		m_pDefaultShader->SetUniformInt("u_BaseTexture", 0);
		SetShader(m_pDefaultShader);
	}

	CTextRenderer::~CTextRenderer() {
		delete m_pDefaultShader;
	}

	void CTextRenderer::DrawCharacterTexture(unsigned int textureId, Vec2 vPosTL, Vec2 vPosBR, const ColorRGB & rgb, float alpha) {
		
		m_pRenderer->Project(& vPosTL);
		m_pRenderer->Project(& vPosBR);

		float vertexBuffer[] = {
			vPosBR.x, vPosTL.y, 0.f, 1.f, 0.f,
			vPosTL.x, vPosTL.y, 0.f, 0.f, 0.f,
			vPosBR.x, vPosBR.y, 0.f, 1.f, 1.f,
			vPosTL.x, vPosBR.y, 0.f, 0.f, 1.f
		};

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertexBuffer, GL_DYNAMIC_DRAW);
		glBindTexture(GL_TEXTURE_2D, textureId);
		m_pShader->Use();
		m_pShader->SetUniformVec4("u_vColor", ONERGB(rgb), alpha);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void CTextRenderer::DrawText(const char * szText, Vec2 vPos) {
		if(!m_pFont) {
			// TODO - 错误信息
			return;
		}

		Vec2 vCurrPos = vPos;

		for(size_t i = 0; szText[i] && szText[i + 1]; i += 2) {
			// TODO - 这里仅仅只是临时测试用，后续会重写，且需要支持 UTF-8
			CFont::CharType character = (static_cast<CFont::CharType>(static_cast<unsigned char>(szText[i + 1])) << 8)
			                          + (static_cast<CFont::CharType>(static_cast<unsigned char>(szText[i])));

			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);

			vCurrPos.y = vPos.y - static_cast<float>(pCharacter->bearing.y) + m_pFont->m_fontSize;
			DrawCharacterTexture(pCharacter->textureId,
				vCurrPos, vCurrPos + Vec2Cast(pCharacter->size),
				m_color, m_alpha
			);
			vCurrPos.x += static_cast<float>(pCharacter->advance.x >> 6);
		}
	}

}

#if 0

#include <FrameCore/Globals.h>
#include <FrameAsset/AssetsManager.h>
#include <FrameMath/ColorMath.h>

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

	CTextRenderer::CTextRenderer(ColorRGB * pColor, uint8 * pAlpha) {
		m_pColor = pColor;
		m_pAlpha = pAlpha;
	}

	/* +-----------------------------------------------+ */
	/* |                   Draw Text                   | */
	/* +-----------------------------------------------+ */

	void CTextRenderer::DrawText(float x, float y, const char * sz, const ColorRGB & rgb, uint8 alpha) {
		SDL_Surface * surface = DrawTextAsSdlSurface(sz, rgb, alpha);
		if (!surface) {
			return;
		}

		SDL_Texture * texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
		if(!texture) {
			SDL_FreeSurface(surface);
			return;
		}

		SDL_FRect destRect {};
		destRect.w = static_cast<float>(surface->w);
		destRect.h = static_cast<float>(surface->h);

		switch (m_pFont->GetHAlign()) {
		case CFont::EHAlign::Left:   destRect.x = x; break;
		case CFont::EHAlign::Center: destRect.x = x - destRect.w / 2; break;
		case CFont::EHAlign::Right:  destRect.x = x - destRect.w; break;
		}
		switch (m_pFont->GetVAlign()) {
		case CFont::EVAlign::Top:    destRect.y = y; break;
		case CFont::EVAlign::Middle: destRect.y = y - destRect.h / 2; break;
		case CFont::EVAlign::Bottom: destRect.y = y - destRect.h; break;
		}

		SDL_RenderCopyF(m_sdlRenderer, texture, 0, & destRect);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		
	}

	CStaticSprite * CTextRenderer::DrawTextAsSprite(const char * sz, const ColorRGB & rgb, uint8 alpha) {
		return gAssetsManager->CreateStaticSprite(DrawTextAsSdlSurface(sz, rgb, alpha));
	}

	SDL_Surface * CTextRenderer::DrawTextAsSdlSurface(const char * sz, const ColorRGB & rgb, uint8 alpha) {
		return TTF_RenderUTF8_Blended_Wrapped(m_pFont->GetSdlFont(), sz, { rgb.r, rgb.g, rgb.b, alpha }, m_autoWrapLength);
	}

}

#endif