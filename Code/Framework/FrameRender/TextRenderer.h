#pragma once

#include <FrameRender/RendererBaseClass.h>

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

#include <FrameAsset/Font.h>

#include <FrameUtility/UTF8Utils.h>
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

		ETextHAlign m_halign = ETextHAlign::Left;
		ETextVAlign m_valign = ETextVAlign::Top;

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

		void SetAlign(std::pair<ETextHAlign, ETextVAlign> align) {
			SetAlign(align.first, align.second);
		}
		void SetAlign(ETextHAlign halign, ETextVAlign valign) {
			m_halign = halign;
			m_valign = valign;
		}
		void SetHAlign(ETextHAlign halign) {
			m_halign = halign;
		}
		void SetVAlign(ETextVAlign valign) {
			m_valign = valign;
		}

		std::pair<ETextHAlign, ETextVAlign> GetAlign() const {
			return { m_halign, m_valign };
		}
		ETextHAlign GetHAlign() const {
			return m_halign;
		}
		ETextVAlign GetVAlign() const {
			return m_valign;
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

		/* +-----------------------------------------------+ */
		/* |                Draw Text Align                | */
		/* +-----------------------------------------------+ */

		void DrawTextAlign(UnicodeStringView unicodeText, const Vec2 & vPos, ETextHAlign halign, ETextVAlign valign);

	private:
		void UseMyShader(const ColorRGB & rgb, float alpha);

	};
}