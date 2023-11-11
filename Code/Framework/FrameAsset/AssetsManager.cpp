#include <FrameAsset/AssetsManager.h>

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

	CFont::CFont(const char * file, int size) {
		m_size = size;
		m_font = TTF_OpenFont(file, size);

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

	CTexture * CAssetsManager::CreateTexture(SDL_Renderer * sdlRenderer, SDL_Surface * sdlSurface) {
		return new CTexture {
			SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface),
			sdlSurface->w, sdlSurface->h
		};
	}
	
	void CAssetsManager::DestroyTexture(CTexture * pTexture) {
		SDL_DestroyTexture(pTexture->texture);
		delete pTexture;
	}

	CFont * CAssetsManager::OpenFont(const char * fontFile, int fontSize) {
		return new CFont { fontFile, fontSize };
	}

	void CAssetsManager::CloseFont(CFont * pFont) {
		delete pFont;
	}

}