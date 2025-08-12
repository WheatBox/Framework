#pragma once

#include "../FrameCore/BasicTypes.h"
#include "../FrameMath/ColorMath.h"
#include "../FrameMath/Vector2.h"

#include "../FrameAsset/Font.h"

#include "../FrameUtility/BitOperation.h"

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

	class CTextRenderer final {

	private:
		CRenderer * m_pRenderer;

		const CShader * m_pShader = nullptr;

		CFont * m_pFont = nullptr;

	public:

		CTextRenderer(CRenderer * pRenderer);

		void ResetShader();
		void SetShader(const CShader * pShader);
		const CShader * GetShader() const;

		void SetFont(CFont * pFont) {
			m_pFont = pFont;
		}
		CFont * GetFont() const {
			return m_pFont;
		}

		/* +-----------------------------------------------+ */
		/* |                   Draw Text                   | */
		/* +-----------------------------------------------+ */

		/* ----- No Wrap ----- */

	private:
		void DrawCharacterTexture(CFont::SCharacter * pCharacter, Vec2 vPos);

		void DrawTextSingleLine__DontUseMyShader(UTF8StringView utf8Text, const Vec2 & vPos) {
			DrawTextSingleLine__DontUseMyShader(UTF8Utils::ToUnicode(utf8Text), vPos);
		}
		void DrawTextSingleLine__DontUseMyShader(UnicodeStringView unicodeText, const Vec2 & vPos);
	public:

		void DrawTextSingleLine(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawTextSingleLine(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, alpha);
		}
		void DrawTextSingleLine(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			UseMyShader(rgb, alpha);
			DrawTextSingleLine__DontUseMyShader(unicodeText, vPos);
		}

		/* ----- \n Wrap ----- */

		void DrawText(UTF8StringView utf8Text, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawText(UTF8Utils::ToUnicode(utf8Text), vPos, rgb, alpha);
		}
		void DrawText(UnicodeStringView unicodeText, const Vec2 & vPos, const ColorRGB & rgb, float alpha);

		/* ----- Auto Wrap ----- */

		void DrawTextAutoWrap(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrap(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, rgb, alpha);
		}
		void DrawTextAutoWrap(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, const ColorRGB & rgb, float alpha);

		/* +-----------------------------------------------+ */
		/* |                Draw Text Align                | */
		/* +-----------------------------------------------+ */

		void DrawTextAlign(UTF8StringView utf8Text, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlign(UTF8Utils::ToUnicode(utf8Text), vPos, 0.f, halign, valign, rgb, alpha);
		}
		void DrawTextAlign(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlign(unicodeText, vPos, 0.f, halign, valign, rgb, alpha);
		}

		void DrawTextAutoWrapAlign(UTF8StringView utf8Text, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapAlign(UTF8Utils::ToUnicode(utf8Text), vPos, _maxLineWidth, halign, valign, rgb, alpha);
		}
		void DrawTextAutoWrapAlign(UnicodeStringView unicodeText, const Vec2 & vPos, float _maxLineWidth, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlign(unicodeText, vPos, m_pFont->TextAutoWrapLineFormats(unicodeText, _maxLineWidth), halign, valign, rgb, alpha);
		}

		/* +-------------------------------------------------------------+ */
		/* |    Draw Text std::vector<CFont::STextAutoWrapLineFormat>    | */
		/* +-------------------------------------------------------------+ */
		
		void DrawTextAutoWrapLineFormats(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlign(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, rgb, alpha);
		}
		void DrawTextAutoWrapLineFormats(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlign(unicodeText, vPos, textAutoWrapLineFormats, ETextHAlign::Left, ETextVAlign::Top, rgb, alpha);
		}
		
		void DrawTextAutoWrapLineFormatsAlign(UTF8StringView utf8Text, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha) {
			DrawTextAutoWrapLineFormatsAlign(UTF8Utils::ToUnicode(utf8Text), vPos, textAutoWrapLineFormats, halign, valign, rgb, alpha);
		}
		void DrawTextAutoWrapLineFormatsAlign(UnicodeStringView unicodeText, const Vec2 & vPos, const std::vector<CFont::STextAutoWrapLineFormat> & textAutoWrapLineFormats, ETextHAlign halign, ETextVAlign valign, const ColorRGB & rgb, float alpha);

	private:
		void UseMyShader(const ColorRGB & rgb, float alpha);

	};
}