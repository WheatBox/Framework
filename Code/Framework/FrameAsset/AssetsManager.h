#pragma once

#include <FrameAsset/Sprite.h>

namespace Frame {

	/*
	class CAnimatedSprite : public ISprite {
	public:
		CAnimatedSprite() = delete;
		CAnimatedSprite(SDL_Renderer * sdlRenderer, SDL_Surface ** sdlSurfaces, int frameCount, int width, int height, const Vec2 & vOffset);
		// TODO - sdlSurfaces to m_frames
		virtual ~CAnimatedSprite() = default;

		virtual SDL_Texture * GetSdlTexture() const override { return m_frames[0]; }
		SDL_Texture * GetSdlTexture(int frame) const { return m_frames[frame % m_frameCount]; }

		SDL_Texture ** GetFrames() const { return m_frames; }
		int GetFrameCount() const { return m_frameCount; }

	private:
		SDL_Texture ** m_frames;
		int m_frameCount;
	};

	class CFont {
	public:
		CFont() = delete;
		CFont(const char * filename, int fontSize);
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
	*/
	class CAssetsManager {
	public:
		CAssetsManager();

		CStaticSprite * CreateStaticSprite(const char * filename) {
			return new CStaticSprite { filename };
		}

		void DestroyStaticSprite(CStaticSprite * pSprite) {
			delete pSprite;
		}
		/*
		CFont * OpenFont(const char * filename, int fontSize) {
			return new CFont { filename, fontSize };
		}

		void CloseFont(CFont * pFont) {
			delete pFont;
		}*/
	};
}
