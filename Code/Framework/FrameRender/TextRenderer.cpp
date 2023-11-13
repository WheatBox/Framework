#include <FrameRender/TextRenderer.h>

#include <FrameCore/Globals.h>
#include <FrameAsset/AssetsManager.h>
#include <FrameMath/ColorMath.h>

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

	CTextRenderer::CTextRenderer(ColorRGB * pColor, Uint8 * pAlpha) {
		m_pColor = pColor;
		m_pAlpha = pAlpha;
	}

	/* +-----------------------------------------------+ */
	/* |                   Draw Text                   | */
	/* +-----------------------------------------------+ */

	void CTextRenderer::DrawText(float x, float y, const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		SDL_Surface * surface = DrawTextAsSdlSurface(sz, rgb, alpha);
		if (!surface) {
			return;
		}

		SDL_Texture * texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
		if(!texture) {
			SDL_FreeSurface(surface);
			return;
		}

		SDL_FRect destRect {};
		destRect.w = static_cast<float>(surface->w);
		destRect.h = static_cast<float>(surface->h);

		switch (m_pFont->GetHAlign()) {
		case CFont::EHAlign::Left:   destRect.x = x; break;
		case CFont::EHAlign::Center: destRect.x = x - destRect.w / 2; break;
		case CFont::EHAlign::Right:  destRect.x = x - destRect.w; break;
		}
		switch (m_pFont->GetVAlign()) {
		case CFont::EVAlign::Top:    destRect.y = y; break;
		case CFont::EVAlign::Middle: destRect.y = y - destRect.h / 2; break;
		case CFont::EVAlign::Bottom: destRect.y = y - destRect.h; break;
		}

		SDL_RenderCopyF(m_sdlRenderer, texture, 0, & destRect);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		
	}

	CStaticSprite * CTextRenderer::DrawTextAsSprite(const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		return gAssetsManager->CreateStaticSprite(DrawTextAsSdlSurface(sz, rgb, alpha));
	}

	SDL_Surface * CTextRenderer::DrawTextAsSdlSurface(const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		return TTF_RenderUTF8_Blended_Wrapped(m_pFont->GetSdlFont(), sz, { rgb.r, rgb.g, rgb.b, alpha }, m_autoWrapLength);
	}

}