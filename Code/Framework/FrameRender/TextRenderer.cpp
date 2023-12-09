#include <FrameRender/TextRenderer.h>

#include <FrameRender/DefaultShaders.h>
#include <FrameRender/Renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	CTextRenderer::CTextRenderer(CRenderer * pRenderer)
		: m_pRenderer { pRenderer }
		, m_pDefaultShader { new CShader {} }
	{
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

	void CTextRenderer::DrawCharacterTexture(CFont::SCharacter * pCharacter, Vec2 vPos) {
		m_pShader->SetUniformVec2("u_vPos", vPos.x, vPos.y);
		glBindVertexArray(pCharacter->m_VAO);
		glBindTexture(GL_TEXTURE_2D, pCharacter->textureId);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

#define __DRAWTEXT_NEXTLINE \
	vBasePos.y += m_pFont->GetLineHeight(); \
	vCurrPos.x = vBasePos.x;

	void CTextRenderer::DrawTextSingleLine(UnicodeStringView unicodeText, const Vec2 & vPos) {
		if(!m_pFont) {
			/* TODO - 错误信息 */
			return;
		}

		UseMyShader(m_color, m_alpha);

		Vec2 vCurrPos = vPos;

		for(CFont::CharType character : unicodeText) {
			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);

			vCurrPos.y = vPos.y - pCharacter->bearing.y + m_pFont->GetFontSize();
			DrawCharacterTexture(pCharacter, vCurrPos);
			vCurrPos.x += pCharacter->advance.x;
		}
	}

	void CTextRenderer::DrawTextBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
		if(!m_pFont) {
			/* TODO - 错误信息 */
			return;
		}

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

	void CTextRenderer::DrawTextAutoWrapBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha) {
		if(!m_pFont) {
			/* TODO - 错误信息 */
			return;
		}

		if(_maxLineWidth <= 0.f) {
			DrawTextBlended(unicodeText, vPos, rgb, alpha);
			return;
		}

		UseMyShader(rgb, alpha);
		
		m_pFont->TextAutoWrapBase(unicodeText, _maxLineWidth,
			[this, & unicodeText, & vPos](size_t _iLineHead, size_t _iLineTail, const Vec2 & _vOffset, float) {
				DrawTextSingleLine(unicodeText.substr(_iLineHead, _iLineTail - _iLineHead + 1), vPos + _vOffset);
			}
		);
	}

	void CTextRenderer::DrawTextAlignAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, float _maxLineWidth) {
		std::vector<CFont::STextAutoWrapLineData> lines = m_pFont->TextAutoWrapLineDataIntoVector(unicodeText, _maxLineWidth);
		
		float xOffsetRatio = 0.f;
		float passageYOffset = 0.f;

		switch(valign) {
		case ETextVAlign::Middle:
			passageYOffset = -(lines.back().vOffset.y + m_pFont->GetLineHeight()) * 0.5f;
			break;
		case ETextVAlign::Bottom:
			passageYOffset = -(lines.back().vOffset.y + m_pFont->GetLineHeight());
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

		for(const auto & current : lines) {
			DrawTextSingleLine(unicodeText.substr(current.headIndex, current.tailIndex - current.headIndex + 1),
				vPos + current.vOffset + Vec2 {
					static_cast<float>(static_cast<int>(current.width * xOffsetRatio)),
					passageYOffset
				}
			);
		}
	}

	void CTextRenderer::UseMyShader(const ColorRGB & rgb, float alpha) {
		m_pShader->Use();

		static ColorRGB __colorPrev = (m_pShader->SetUniformVec4("u_vColor", ONERGB(rgb), alpha), rgb);
		static float __alphaPrev = alpha;
		if(__colorPrev != rgb || __alphaPrev != alpha) {
			m_pShader->SetUniformVec4("u_vColor", ONERGB(rgb), alpha);
			__colorPrev = rgb;
			__alphaPrev = alpha;
		}

		static int __windowWidthPrev = -1, __windowHeightPrev = -1;
		if(__windowWidthPrev != m_pRenderer->GetWindowWidth() || __windowHeightPrev != m_pRenderer->GetWindowHeight()) {
			__windowWidthPrev = m_pRenderer->GetWindowWidth();
			__windowHeightPrev = m_pRenderer->GetWindowHeight();
			m_pShader->SetUniformVec2("u_vWindowSize", static_cast<float>(__windowWidthPrev), static_cast<float>(__windowHeightPrev));
		}
	}

#undef __DRAWTEXT_NEXTLINE

}