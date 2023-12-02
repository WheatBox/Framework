#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

#include <FrameAsset/Font.h>

namespace Frame {

	class CRenderer;
	class CShader;

	class CTextRenderer {

	private:
		CRenderer * m_pRenderer;

		unsigned int m_VBO, m_VAO;

		const ColorRGB & m_color;
		const float & m_alpha;

		struct SDefault {
		};

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

		void DrawCharacterTexture(unsigned int textureId, Vec2 vPosTL, Vec2 vPosBR, const ColorRGB & rgb, float alpha);

		void DrawText(const char * szText, Vec2 vPos);

	};
}

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