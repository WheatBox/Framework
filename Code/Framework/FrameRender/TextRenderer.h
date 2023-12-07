#pragma once

#include <FrameRender/RendererBaseClass.h>

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

#include <FrameAsset/Font.h>

#include <FrameUtility/UTF8Utils.h>

namespace Frame {

	class CRenderer;
	class CShader;

	class CTextRenderer : public RendererBaseClass::IColorAlpha {

	private:
		CRenderer * m_pRenderer;

		CShader * const m_pDefaultShader;
		CShader * m_pShader = nullptr;

		CFont * m_pFont = nullptr;

	public:

		CTextRenderer(CRenderer * pRenderer);
		virtual ~CTextRenderer();

		void ResetShader() { m_pShader = m_pDefaultShader; }
		void SetShader(CShader * pShader) { m_pShader = pShader; }
		CShader * GetShader() const { return m_pShader; }

		void SetFont(CFont * pFont) {
			m_pFont = pFont;
		}
		CFont * GetFont() const {
			return m_pFont;
		}

		/* +-----------------------------------------------+ */
		/* |                   Draw Text                   | */
		/* +-----------------------------------------------+ */

		void DrawCharacterTexture(CFont::SCharacter * pCharacter, Vec2 vPos);

		/* ----- No Wrap ----- */

		void DrawTextNoWrap(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawTextNoWrap(UTF8Utils::ToUnicode(utf8Text), vPos);
		}
		void DrawTextNoWrap(UnicodeStringView unicodeText, const Vec2 & vPos);

		/* ----- \n Wrap ----- */

		void DrawText(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawText(UTF8Utils::ToUnicode(utf8Text), vPos);
		}
		void DrawText(UnicodeStringView unicodeText, const Vec2 & vPos) {
			DrawTextBlended(unicodeText, vPos, m_color, m_alpha);
		}
		
		void DrawTextColorBlended(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb) {
			DrawTextBlended(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, m_alpha);
		}
		void DrawTextColorBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb) {
			DrawTextBlended(unicodeText, vPos, rgb, m_alpha);
		}

		void DrawTextAlphaBlended(UTF8StringView utf8Text, const Vec2 & vPos, float alpha) {
			DrawTextBlended(UTF8Utils::ToUnicode(utf8Text), vPos, m_color, alpha);
		}
		void DrawTextAlphaBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float alpha) {
			DrawTextBlended(unicodeText, vPos, m_color, alpha);
		}

		void DrawTextBlended(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawTextBlended(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, alpha);
		}
		void DrawTextBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha);

		/* ----- Auto Wrap ----- */

		void DrawTextAutoWrap(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth) {
			DrawTextAutoWrap(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth);
		}
		void DrawTextAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth);

		/* --------------------- */

	private:
		void UseMyShader(const ColorRGB & rgb, float alpha);

	};
}