#pragma once

#if 0

#include <FrameCore/BasicTypes.h>
#include <FrameRender/IRenderer.h>
#include <FrameMath/Vector2.h>

namespace Frame {

	struct ColorRGB;

	class CTextRenderer : public IRenderer {

	public:

		CTextRenderer() = delete;
		CTextRenderer(ColorRGB * pColor, uint8 * pAlpha);
		virtual ~CTextRenderer() = default;

	private:
		ColorRGB * m_pColor = nullptr;
		uint8 * m_pAlpha = nullptr;

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

		void DrawText(const Vec2 & vPos, const char * sz) {
			DrawText(vPos.x, vPos.y, sz);
		}
		void DrawText(float x, float y, const char * sz) {
			DrawText(x, y, sz, * m_pColor, * m_pAlpha);
		}
		void DrawText(const Vec2 & vPos, const char * sz, const ColorRGB & rgb, uint8 alpha) {
			DrawText(vPos.x, vPos.y, sz, rgb, alpha);
		}
		void DrawText(float x, float y, const char * sz, const ColorRGB & rgb, uint8 alpha);

		CStaticSprite * DrawTextAsSprite(const char * sz, const ColorRGB & rgb, uint8 alpha);

		SDL_Surface * DrawTextAsSdlSurface(const char * sz, const ColorRGB & rgb, uint8 alpha);

	};

}

#endif