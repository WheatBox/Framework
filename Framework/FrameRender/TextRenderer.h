#pragma once

#include <FrameRender/RendererBase.h>

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

	class CTextRenderer : public RendererBase::IColorAlpha {

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

		void DrawTextSingleLineColorBlended(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb) {
			DrawTextSingleLineBlended(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, m_alpha);
		}
		void DrawTextSingleLineColorBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb) {
			DrawTextSingleLineBlended(unicodeText, vPos, rgb, m_alpha);
		}

		void DrawTextSingleLineAlphaBlended(UTF8StringView utf8Text, const Vec2 & vPos, float alpha) {
			DrawTextSingleLineBlended(UTF8Utils::ToUnicode(utf8Text), vPos, m_color, alpha);
		}
		void DrawTextSingleLineAlphaBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float alpha) {
			DrawTextSingleLineBlended(unicodeText, vPos, m_color, alpha);
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
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, 0.f, halign, valign, m_color, m_alpha);
		}
		void DrawTextAlign(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, 0.f, halign, valign, m_color, m_alpha);
		}

		void DrawTextAlignColorBlended(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, 0.f, halign, valign, rgb, m_alpha);
		}
		void DrawTextAlignColorBlended(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, 0.f, halign, valign, rgb, m_alpha);
		}

		void DrawTextAlignAlphaBlended(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, float alpha) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, 0.f, halign, valign, m_color, alpha);
		}
		void DrawTextAlignAlphaBlended(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, float alpha) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, 0.f, halign, valign, m_color, alpha);
		}

		void DrawTextAlignBlended(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, 0.f, halign, valign, rgb, alpha);
		}
		void DrawTextAlignBlended(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, 0.f, halign, valign, rgb, alpha);
		}

		void DrawTextAutoWrapAlign(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, halign, valign, m_color, m_alpha);
		}
		void DrawTextAutoWrapAlign(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, _maxLineWidth, halign, valign, m_color, m_alpha);
		}

		void DrawTextAutoWrapAlignColorBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, halign, valign, rgb, m_alpha);
		}
		void DrawTextAutoWrapAlignColorBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, _maxLineWidth, halign, valign, rgb, m_alpha);
		}

		void DrawTextAutoWrapAlignAlphaBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, float alpha) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, halign, valign, m_color, alpha);
		}
		void DrawTextAutoWrapAlignAlphaBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, float alpha) {
			DrawTextAutoWrapAlignBlended(unicodeText, vPos, _maxLineWidth, halign, valign, m_color, alpha);
		}

		void DrawTextAutoWrapAlignBlended(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, halign, valign, rgb, alpha);
		}
		void DrawTextAutoWrapAlignBlended(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlignBlended(unicodeText, vPos, m_pFont->TextAutoWrapLineFormats(unicodeText, _maxLineWidth), halign, valign, rgb, alpha);
		}

		/* +-------------------------------------------------------------+ */
		/* |    Draw Text std::vector<CFont::STextAutoWrapLineFormat>    | */
		/* +-------------------------------------------------------------+ */
		
		void DrawTextAutoWrapLineFormats(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats) {
			DrawTextAutoWrapLineFormatsAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, m_color, m_alpha);
		}
		void DrawTextAutoWrapLineFormats(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats) {
			DrawTextAutoWrapLineFormatsAlignBlended(unicodeText, vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, m_color, m_alpha);
		}

		void DrawTextAutoWrapLineFormatsAlign(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAutoWrapLineFormatsAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, halign, valign, m_color, m_alpha);
		}
		void DrawTextAutoWrapLineFormatsAlign(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign) {
			DrawTextAutoWrapLineFormatsAlignBlended(unicodeText, vPos, textAutoWrapLineFormats, halign, valign, m_color, m_alpha);
		}
		
		void DrawTextAutoWrapLineFormatsBlended(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, rgb, alpha);
		}
		void DrawTextAutoWrapLineFormatsBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlignBlended(unicodeText, vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, rgb, alpha);
		}
		
		void DrawTextAutoWrapLineFormatsAlignBlended(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlignBlended(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, halign, valign, rgb, alpha);
		}
		void DrawTextAutoWrapLineFormatsAlignBlended(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha);

	private:
		void UseMyShader(const ColorRGB & rgb, float alpha);

	};
}