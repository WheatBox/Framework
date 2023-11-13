#include <FrameAsset/AssetsManager.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

	CStaticSprite::CStaticSprite(SDL_Surface * sdlSurface, const Vec2 & vOffset, bool bFreeSurface) {
		m_sdlTexture = SDL_CreateTextureFromSurface(gRenderer->GetSdlRenderer(), sdlSurface);
		if(m_sdlTexture) {
			m_width = sdlSurface->w;
			m_height = sdlSurface->h;
			m_vOffset = vOffset;
		}
		if(bFreeSurface) {
			SDL_FreeSurface(sdlSurface);
		}
	}

	CStaticSprite::~CStaticSprite() {
		SDL_DestroyTexture(m_sdlTexture);
	}

	CFont::CFont(const char * filename, int fontSize) {
		m_size = fontSize;
		m_font = TTF_OpenFont(filename, fontSize);

		SetWrappedAlign(EWrappedAlign::Left);
	}

	CFont::~CFont() {
		TTF_CloseFont(m_font);
	}

	void CFont::SetSize(int size) {
		m_size = size;
		TTF_SetFontSize(m_font, size);
	}

	void CFont::SetWrappedAlign(EWrappedAlign wrappedAlign) {
		TTF_SetFontWrappedAlign(m_font, static_cast<int>(wrappedAlign));
	}

	CAssetsManager::CAssetsManager() {
		if(!TTF_WasInit()) {
			TTF_Init();
		}
	}

}