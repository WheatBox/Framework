#pragma once

#include <FrameRender/RendererBaseClass.h>

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

#include <FrameAsset/Font.h>

#include <FrameUtility/BitOperation.h>

namespace Frame {

	class CRenderer;
	class CShader;

	// 文本横向对齐
	// Text Horizontal Align
	enum class ETextHAlign : uint8 {
		Left,
		Center,
		Right,
	};

	// 文本纵向对齐
	// Text Vertical Align
	enum class ETextVAlign : uint8 {
		Top,
		Middle,
		Bottom,
	};

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

	private:
		void DrawTextSingleLine__DontUseMyShader(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawTextSingleLine__DontUseMyShader(UTF8Utils::ToUnicode(utf8Text), vPos);
		}
		void DrawTextSingleLine__DontUseMyShader(UnicodeStringView unicodeText, const Vec2 & vPos);
	public:

		void DrawTextSingleLine(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawTextSingleLineBlended(UTF8Utils::ToUnicode(utf8Text), vPos, m_color, m_alpha);
		}
		void DrawTextSingleLine(UnicodeStringView unicodeText, const Vec2 & vPos) {
			DrawTextSingleLineBlended(unicodeText, vPos, m_color, m_alpha);
		}
		
		void DrawTextSingleLineBlended(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawTextSingleLineBlended(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, alpha);
		}
		void DrawTextSingleLineBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			UseMyShader(rgb, alpha);
			DrawTextSingleLine__DontUseMyShader(unicodeText, vPos);
		}

		/* ----- \n Wrap ----- */

		void DrawText(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawTextBlended(UTF8Utils::ToUnicode(utf8Text), vPos, m_color, m_alpha);
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
			DrawTextAutoWrapBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, m_color, m_alpha);
		}
		void DrawTextAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth) {
			DrawTextAutoWrapBlended(unicodeText, vPos, _maxLineWidth, m_color, m_alpha);
		}

		void DrawTextAutoWrapColorBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb) {
			DrawTextAutoWrapBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, rgb, m_alpha);
		}
		void DrawTextAutoWrapColorBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb) {
			DrawTextAutoWrapBlended(unicodeText, vPos, _maxLineWidth, rgb, m_alpha);
		}

		void DrawTextAutoWrapAlphaBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, float alpha) {
			DrawTextAutoWrapBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, m_color, alpha);
		}
		void DrawTextAutoWrapAlphaBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, float alpha) {
			DrawTextAutoWrapBlended(unicodeText, vPos, _maxLineWidth, m_color, alpha);
		}

		void DrawTextAutoWrapBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, rgb, alpha);
		}
		void DrawTextAutoWrapBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha);

		/* +-----------------------------------------------+ */
		/* |                Draw Text Align                | */
		/* +-----------------------------------------------+ */

		void DrawTextAlign(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAlignAutoWrap(UTF8Utils::ToUnicode(utf8Text), vPos, halign, valign, 0.f);
		}
		void DrawTextAlign(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAlignAutoWrap(unicodeText, vPos, halign, valign, 0.f);
		}
		
		void DrawTextAlignAutoWrap(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, float _maxLineWidth) {
			DrawTextAlignAutoWrap(UTF8Utils::ToUnicode(utf8Text), vPos, halign, valign, _maxLineWidth);
		}
		void DrawTextAlignAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, float _maxLineWidth);

	private:
		void UseMyShader(const ColorRGB & rgb, float alpha);

	};
}