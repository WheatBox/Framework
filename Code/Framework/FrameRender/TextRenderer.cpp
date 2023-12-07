#include <FrameRender/TextRenderer.h>

#include <FrameRender/DefaultShaders.h>
#include <FrameRender/Renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_set>
#include <iostream>

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
	vBasePos.y += m_pFont->m_lineHeight; \
	vCurrPos.x = vBasePos.x;

	void CTextRenderer::DrawTextNoWrap(UnicodeStringView unicodeText, const Vec2 & vPos) {
		if(!m_pFont) {
			/* TODO - 错误信息 */
			return;
		}

		UseMyShader(m_color, m_alpha);

		Vec2 vCurrPos = vPos;

		for(CFont::CharType character : unicodeText) {
			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);

			vCurrPos.y = vPos.y - pCharacter->bearing.y + m_pFont->m_fontSize;
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
			
			vCurrPos.y = vBasePos.y - pCharacter->bearing.y + m_pFont->m_fontSize;
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

	void CTextRenderer::DrawTextAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth) {
		if(!m_pFont) {
			/* TODO - 错误信息 */
			return;
		}

		if(_maxLineWidth <= 0.f) {
			DrawText(unicodeText, vPos);
		}

		constexpr size_t iInvalid = static_cast<size_t>(-1);
		size_t iLineHead = 0, iLineTail = 0, iPrevNotWordChar = iInvalid;

		Vec2 vBasePos = vPos;
		Vec2 vCurrPos = vBasePos;

		for(size_t i = 0, len = unicodeText.length(); i < len; i++) {
			CFont::CharType character = unicodeText[i];

#define __DRAWTEXTAUTOWRAP_DRAW_AND_NEXTLINE(_pos, _set_iLineTail_code) \
	_set_iLineTail_code \
	DrawTextNoWrap(unicodeText.substr(iLineHead, iLineTail - iLineHead), _pos); \
	__DRAWTEXT_NEXTLINE; \
	iLineHead = iLineTail; \
	iPrevNotWordChar = iInvalid;

			if(character == '\n') {
				__DRAWTEXTAUTOWRAP_DRAW_AND_NEXTLINE(vBasePos,
					iLineTail = i + 1;
				);
				continue;
			}

			CFont::SCharacter * pCharacter = m_pFont->GetOrInitCharacter(character);
			vCurrPos.y = vBasePos.y - pCharacter->bearing.y + m_pFont->m_fontSize;

			bool bCurrentIsNotWordChar = !__IsWordChar(character);
			if(bCurrentIsNotWordChar) {
				iPrevNotWordChar = i;
			}

			if(vCurrPos.x > vBasePos.x + _maxLineWidth) {
				if(bCurrentIsNotWordChar) {
					__DRAWTEXTAUTOWRAP_DRAW_AND_NEXTLINE(vBasePos,
						if(iLineTail == iLineHead) {
							iLineTail = (character == ' ' ? i + 1 : i);
						}
						i = iLineTail - 1;
					);
				} else {
					if(iPrevNotWordChar != iInvalid && !__IsWordChar(unicodeText[iPrevNotWordChar])) {
						__DRAWTEXTAUTOWRAP_DRAW_AND_NEXTLINE(vBasePos,
							iLineTail = iPrevNotWordChar + 1;
							i = iPrevNotWordChar;
						);
					}
					vCurrPos.x += pCharacter->advance.x;
				}
			} else {
				if(bCurrentIsNotWordChar) {
					if(character == ' ') {
						iLineTail = i + 1;
						iPrevNotWordChar = iInvalid;
					} else {
						iLineTail = i;
					}
				}
				vCurrPos.x += pCharacter->advance.x;
			}

#undef __DRAWTEXTAUTOWRAP_DRAW_AND_NEXTLINE
		}
		DrawTextNoWrap(unicodeText.substr(iLineHead), vBasePos);
	}

	void CTextRenderer::UseMyShader(const ColorRGB & rgb, float alpha) {
		m_pShader->Use();
		m_pShader->SetUniformVec4("u_vColor", ONERGB(rgb), alpha);
		m_pShader->SetUniformVec2("u_vWindowSize", static_cast<float>(m_pRenderer->GetWindowWidth()), static_cast<float>(m_pRenderer->GetWindowHeight()));
	}

#undef __DRAWTEXT_NEXTLINE

}