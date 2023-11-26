#include <FrameAsset/AssetsManager.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>

namespace Frame {



}

#if 0
#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

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
#endif