#pragma once

#include <FrameRender/IRenderer.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	class CTextRenderer : public IRenderer {

	public:

		CTextRenderer() = delete;
		CTextRenderer(ColorRGB * pColor, Uint8 * pAlpha);
		virtual ~CTextRenderer() = default;

	private:
		ColorRGB * m_pColor = nullptr;
		Uint8 * m_pAlpha = nullptr;

		CFont * m_pFont = nullptr;

		int m_autoWrapLength = 0;

	public:

		void SetFont(CFont * pFont) { m_pFont = pFont; }

		CFont * GetFont() const { return m_pFont; }

		void SetAutoWrapLength(int autoWrapLength) { m_autoWrapLength = autoWrapLength; }

		int GetAutoWrapLength() const { return m_autoWrapLength; }

		/* +-----------------------------------------------+ */
		/* |                   Draw Text                   | */
		/* +-----------------------------------------------+ */

		void DrawText(int x, int y, const char * sz) {
			DrawText(x, y, sz, * m_pColor, * m_pAlpha);
		}
		void DrawText(float x, float y, const char * sz) {
			DrawText(x, y, sz, * m_pColor, * m_pAlpha);
		}
		void DrawText(int x, int y, const char * sz, const ColorRGB & rgb, Uint8 alpha);
		void DrawText(float x, float y, const char * sz, const ColorRGB & rgb, Uint8 alpha);

		CTexture * DrawTextAsTexture(const char * sz, const ColorRGB & rgb, Uint8 alpha);

	};

}