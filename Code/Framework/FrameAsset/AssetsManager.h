#pragma once

#include <FrameRender/BasicRenderingTypes.h>

#include <vector>

namespace Frame {

	class CTexture {
	public:
		CTexture() = delete;
		CTexture(SDL_Texture * _texture, int _width, int _height)
			: texture(_texture)
			, width(_width)
			, height(_height)
		{}
		virtual ~CTexture() = default;

		SDL_Texture * texture = nullptr;
		int width = 0;
		int height = 0;
	};

	class CFont {
	public:
		CFont() = delete;
		CFont(const char * file, int size);
		virtual ~CFont();

		enum class EHAlign {
			Left = 0,
			Center = 1,
			Right = 2
		};
		enum class EVAlign {
			Top = 0,
			Middle = 1,
			Bottom = 2
		};

		typedef EHAlign EWrappedAlign;

		TTF_Font * GetSdlFont() const { return m_font; }

		void SetSize(int size);
		int GetSize() const { return m_size; }

		void SetWrappedAlign(EWrappedAlign wrappedAlign);

		EWrappedAlign GetWrappedAlign() const { return m_wrappedAlign; }

		void SetAlign(EHAlign hAlign, EVAlign vAlign, bool bAlsoSetWrappedAlign = true) {
			SetHAlign(hAlign, bAlsoSetWrappedAlign);
			SetVAlign(vAlign);
		}
		void SetHAlign(EHAlign hAlign, bool bAlsoSetWrappedAlign = true) {
			m_hAlign = hAlign;
			if(bAlsoSetWrappedAlign) {
				SetWrappedAlign(hAlign);
			}
		}
		void SetVAlign(EVAlign vAlign) { m_vAlign = vAlign; }

		EHAlign GetHAlign() const { return m_hAlign; }
		EVAlign GetVAlign() const { return m_vAlign; }

	private:
		TTF_Font * m_font = nullptr;
		int m_size = 0;
		EHAlign m_hAlign = EHAlign::Left;
		EVAlign m_vAlign = EVAlign::Top;
		EWrappedAlign m_wrappedAlign {};
	};

	class CAssetsManager {
	public:
		CAssetsManager();

		CTexture * CreateTexture(SDL_Renderer * sdlRenderer, SDL_Surface * sdlSurface);
		void DestroyTexture(CTexture * pTexture);

		CFont * OpenFont(const char * fontFile, int fontSize);
		void CloseFont(CFont * pFont);
	};
}
