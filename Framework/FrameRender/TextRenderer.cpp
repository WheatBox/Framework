#include "TextRenderer.h"

#include "../FrameRender/DefaultShaders.h"
#include "../FrameRender/Renderer.h"
#include "../FrameRender/RendererBase.h"
#include "../FrameRender/Shader.h"
#include "../FrameCore/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	static CShader * pDefaultShader = nullptr;

	CTextRenderer::CTextRenderer(CRenderer * pRenderer)
		: m_pRenderer { pRenderer }
	{
		if(!pDefaultShader) {
			pDefaultShader = new CShader;
			if(!pDefaultShader->CompileFiles(DEFAULT_TEXT_SHADER_FILES)) {
				Log::Log(Log::ELevel::Error, "Failed to load or compile default text shader files: %s; %s; So now using in-build default text shaders", DEFAULT_TEXT_SHADER_FILES);
				pDefaultShader->Compile(DEFAULT_TEXT_SHADER);
			}
		}
		SetShader(pDefaultShader);
		m_pRenderer->SetUniformInt("u_BaseTexture", 0);
	}

	void CTextRenderer::ResetShader() {
		SetShader(pDefaultShader);
	}

	void CTextRenderer::SetShader(const CShader * pShader) {
		m_pShader = pShader;
		m_pRenderer->__UseShader(m_pShader);
	}

	const CShader * CTextRenderer::GetShader() const {
		return m_pShader;
	}

	void CTextRenderer::DrawCharacterTexture(CFont::SCharacter * pCharacter, Vec2 vPos) {
		m_pRenderer->SetUniformVec2("u_vPos", vPos.x, vPos.y);
		RendererBase::BindVAO(pCharacter->m_VAO);
		RendererBase::BindTextureId(pCharacter->textureId);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

#define __DRAWTEXT_CHECK_FONT_BEFORE_DRAWING \
if(!m_pFont) { \
	Log::Log(Log::ELevel::Error, "Font not set before drawing text"); \
	return; \
}

	void CTextRenderer::DrawTextSingleLine__DontUseMyShader(UnicodeStringView unicodeText, const Vec2 & vPos) {
		__DRAWTEXT_CHECK_FONT_BEFORE_DRAWING

		Vec2 vCurrPos = vPos;

		for(CFont::CharType character : unicodeText) {
			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);

			vCurrPos.y = vPos.y - pCharacter->bearing.y + m_pFont->GetFontSize();
			DrawCharacterTexture(pCharacter, vCurrPos);
			vCurrPos.x += pCharacter->advance.x;
		}
	}

#define __DRAWTEXT_NEXTLINE \
	vBasePos.y += m_pFont->GetLineHeight(); \
	vCurrPos.x = vBasePos.x;

	void CTextRenderer::DrawText(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
		__DRAWTEXT_CHECK_FONT_BEFORE_DRAWING

		UseMyShader(rgb, alpha);
		
		Vec2 vBasePos = vPos;
		Vec2 vCurrPos = vBasePos;
		
		for(CFont::CharType character : unicodeText) {

			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);
			if(character == '\n') {
				__DRAWTEXT_NEXTLINE
				continue;
			}
			
			vCurrPos.y = vBasePos.y - pCharacter->bearing.y + m_pFont->GetFontSize();
			DrawCharacterTexture(pCharacter, vCurrPos);
			vCurrPos.x += pCharacter->advance.x;
			
		}
	}

	inline static bool __IsWordChar(CFont::CharType character) {
		static std::unordered_set<UnicodeChar> __wordCharSet {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'~', '`', '!', '@', '#', '$', '%', '^', '&', '_', '=',
			'+', /* '-',*/ '*', '/', '<', '>', ',', '.', '?', '\'', '\"', '\\', '|',
			'(', ')', '[', ']', '{', '}'
		};
		static auto __end = __wordCharSet.end();
		return __wordCharSet.find(character) != __end;
	}

	void CTextRenderer::DrawTextAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha) {
		__DRAWTEXT_CHECK_FONT_BEFORE_DRAWING

		if(_maxLineWidth <= 0.f) {
			DrawText(unicodeText, vPos, rgb, alpha);
			return;
		}

		UseMyShader(rgb, alpha);
		
		m_pFont->TextAutoWrapBase(unicodeText, _maxLineWidth,
			[this, & unicodeText, & vPos](size_t _iLineHead, size_t _iLineTail, const Vec2 & _vOffset, float) {
				DrawTextSingleLine__DontUseMyShader(unicodeText.substr(_iLineHead, _iLineTail - _iLineHead + 1), vPos + _vOffset);
			}
		);
	}

	void CTextRenderer::DrawTextAutoWrapLineFormatsAlign(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
		if(textAutoWrapLineFormats.empty()) {
			return;
		}

		UseMyShader(rgb, alpha);

		float xOffsetRatio = 0.f;
		float passageYOffset = 0.f;

		switch(valign) {
		case ETextVAlign::Middle:
			passageYOffset = -(textAutoWrapLineFormats.back().vOffset.y + m_pFont->GetLineHeight()) * 0.5f;
			break;
		case ETextVAlign::Bottom:
			passageYOffset = -(textAutoWrapLineFormats.back().vOffset.y + m_pFont->GetLineHeight());
			break;
		}

		switch(halign) {
		case ETextHAlign::Center:
			xOffsetRatio = -0.5f;
			break;
		case ETextHAlign::Right:
			xOffsetRatio = -1.f;
			break;
		}

		for(const auto & current : textAutoWrapLineFormats) {
			DrawTextSingleLine__DontUseMyShader(unicodeText.substr(current.headIndex, current.tailIndex - current.headIndex + 1),
				vPos + current.vOffset + Vec2 {
					static_cast<float>(static_cast<int>(current.width * xOffsetRatio)),
					passageYOffset
				}
			);
		}
	}

	void CTextRenderer::UseMyShader(const ColorRGB & rgb, float alpha) {
		m_pRenderer->__UseShader(m_pShader);
		m_pRenderer->__SetUniformProjMat();
		m_pRenderer->SetUniformVec4("u_vColor", ONERGB(rgb), alpha);
	}

#undef __DRAWTEXT_NEXTLINE
#undef __DRAWTEXT_CHECK_FONT_BEFORE_DRAWING

}
