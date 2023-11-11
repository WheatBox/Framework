#include <FrameRender/TextRenderer.h>

#include <FrameCore/Globals.h>
#include <FrameAsset/AssetsManager.h>

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

#define __CTextRenderer_DrawText(SDL_Rect_Type, SDL_RenderCopy_Func, cast) \
	CTexture * texture = DrawTextAsTexture(sz, rgb, alpha); \
	if(!texture) { \
		return; \
	} \
	SDL_Rect_Type destRect {}; \
	destRect.w = cast(texture->width); \
	destRect.h = cast(texture->height); \
	switch(m_pFont->GetHAlign()) { \
	case CFont::EHAlign::Left:   destRect.x = x; break; \
	case CFont::EHAlign::Center: destRect.x = x - destRect.w / 2; break; \
	case CFont::EHAlign::Right:  destRect.x = x - destRect.w; break; \
	} \
	switch(m_pFont->GetVAlign()) { \
	case CFont::EVAlign::Top:    destRect.y = y; break; \
	case CFont::EVAlign::Middle: destRect.y = y - destRect.h / 2; break; \
	case CFont::EVAlign::Bottom: destRect.y = y - destRect.h; break; \
	} \
	\
	SDL_RenderCopy_Func(m_sdlRenderer, texture->texture, 0, & destRect); \
	gAssetsManager->DestroyTexture(texture);

	void CTextRenderer::DrawText(int x, int y, const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		__CTextRenderer_DrawText(SDL_Rect, SDL_RenderCopy, )
	}
	void CTextRenderer::DrawText(float x, float y, const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		__CTextRenderer_DrawText(SDL_FRect, SDL_RenderCopyF, static_cast<float>)
	}

#undef __CTextRenderer_DrawTextAlign

	CTexture * CTextRenderer::DrawTextAsTexture(const char * sz, const ColorRGB & rgb, Uint8 alpha) {
		SDL_Surface * surface = TTF_RenderUTF8_Blended_Wrapped(m_pFont->GetSdlFont(), sz, { rgb.r, rgb.g, rgb.b, alpha }, m_autoWrapLength);
		if(!surface) {
			return nullptr;
		}

		CTexture * pTexture = gAssetsManager->CreateTexture(m_sdlRenderer, surface);

		SDL_FreeSurface(surface);
		return pTexture;
	}

}