#pragma once

#include <FrameRender/BasicRenderingTypes.h>

#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	struct ISprite {

		virtual SDL_Texture * GetSdlTexture() const = 0;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		const Vec2 & GetOffset() const { return m_vOffset; }
		float GetXOffset() const { return m_vOffset.x; }
		float GetYOffset() const { return m_vOffset.y; }

		void SetOffset(const Vec2 & vOffset) { m_vOffset = vOffset; }

	protected:
		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

	class CStaticSprite : public ISprite {
	public:
		CStaticSprite() = delete;

		CStaticSprite(SDL_Surface * sdlSurface, bool bFreeSurface)
			: CStaticSprite(sdlSurface, { 0, 0 }, bFreeSurface)
		{}
		CStaticSprite(SDL_Surface * sdlSurface, const Vec2 & vOffset, bool bFreeSurface);

		CStaticSprite(const char * filename); // TODO
		
		// TODO - 若无法正常初始化，则将 sdlTexture 设为一张错误提示图片

		virtual ~CStaticSprite();

		virtual SDL_Texture * GetSdlTexture() const override { return m_sdlTexture; }

		void SetColorBlend(const ColorRGB & rgb) {
			SetColorBlend(rgb.r, rgb.g, rgb.b);
		}
		void SetColorBlend(Uint8 r, Uint8 g, Uint8 b);
		void SetAlphaBlend(Uint8 alpha);

		ColorRGB GetColorBlend() const {
			ColorRGB rgb;
			GetColorBlend(& rgb.r, & rgb.g, & rgb.b);
			return rgb;
		}
		void GetColorBlend(Uint8 * destR, Uint8 * destG, Uint8 * destB) const;
		Uint8 GetAlphaBlend() const {
			Uint8 res;
			GetAlphaBlend(& res);
			return res;
		}
		void GetAlphaBlend(Uint8 * destAlpha) const;

	private:
		SDL_Texture * m_sdlTexture;
	};
	
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

	class CAssetsManager {
	public:
		CAssetsManager();

		CStaticSprite * CreateStaticSprite(SDL_Surface * sdlSurface, bool bFreeSurface = true) {
			return new CStaticSprite { sdlSurface, bFreeSurface };
		}

		CStaticSprite * CreateStaticSprite(SDL_Surface * sdlSurface, const Vec2 & vOffset, bool bFreeSurface = true) {
			return new CStaticSprite { sdlSurface, vOffset, bFreeSurface };
		}

		CStaticSprite * CreateStaticSprite(const char * filename) {
			return new CStaticSprite { filename };
		}

		void DestroyStaticSprite(CStaticSprite * pSprite) {
			delete pSprite;
		}

		CFont * OpenFont(const char * filename, int fontSize) {
			return new CFont { filename, fontSize };
		}

		void CloseFont(CFont * pFont) {
			delete pFont;
		}
	};
}
