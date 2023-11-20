#pragma once

#include <FrameMath/ColorMath.h>

#include <FrameMath/Vector2.h>

#include <SDL_blendmode.h>

struct SDL_Renderer;
struct SDL_Window;

namespace Frame {

	class CShapeRenderer;
	class CTextRenderer;

	class CStaticSprite;

	class CRenderer {

	public:
		CRenderer() = default;
		virtual ~CRenderer() = default;

		void Initialize(SDL_Window * sdlWindow);

		SDL_Renderer * GetSdlRenderer() const {
			return m_sdlRenderer;
		}

		CShapeRenderer * pShapeRenderer = nullptr;
		CTextRenderer * pTextRenderer = nullptr;

		enum class EBlendMode {

			// 从 SDL_blendmode.h 里面复制过来的（包括注释）
			// Copied from SDL_blendmode.h (including comments)

			// no blending
			// dstRGBA = srcRGBA
			None = SDL_BLENDMODE_NONE,

			// alpha blending
			// dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
			// dstA = srcA + (dstA * (1-srcA))
			Blend = SDL_BLENDMODE_BLEND,

			// additive blending
			// dstRGB = (srcRGB * srcA) + dstRGB
			// dstA = dstA
			Add = SDL_BLENDMODE_ADD,
			
			// color modulate
			// dstRGB = srcRGB * dstRGB
			// dstA = dstA
			Mod = SDL_BLENDMODE_MOD,

			// color multiply
			// dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
			// dstA = dstA
			Multi = SDL_BLENDMODE_MUL,
			
			Invalid = SDL_BLENDMODE_INVALID
		};

	private:
		SDL_Renderer * m_sdlRenderer = nullptr;

		ColorRGB m_backgroundColor { 0, 0, 0 };

		ColorRGB m_color { 255, 255, 255 };
		Uint8 m_alpha = 255;
		EBlendMode m_blendMode {};

	public:

		void RenderBegin();
		void RenderEnd();

		/* +-----------------------------------------------+ */
		/* |                Set Draw Params                | */
		/* +-----------------------------------------------+ */

		void SetColor(const ColorRGB & rgb) {
			SetColorAlpha(rgb.r, rgb.g, rgb.b, m_alpha);
		}
		void SetColor(Uint8 r, Uint8 g, Uint8 b) {
			SetColorAlpha(r, g, b, m_alpha);
		}
		void SetAlpha(Uint8 alpha) {
			SetColorAlpha(m_color.r, m_color.g, m_color.b, alpha);
		}
		void SetColorAlpha(const ColorRGB & rgb, Uint8 alpha) {
			SetColorAlpha(rgb.r, rgb.g, rgb.b, alpha);
		}
		void SetColorAlpha(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);

		const ColorRGB & GetColor() const { return m_color; }
		Uint8 GetAlpha() const { return m_alpha; }

		void SetBackgroundColor(const ColorRGB & rgb) {
			m_backgroundColor = rgb;
		}
		void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b) {
			m_backgroundColor.Set(r, g, b);
		}

		const ColorRGB & GetBackgroundColor() const { return m_backgroundColor; }

		void SetBlendMode(EBlendMode blendMode);

		EBlendMode GetBlendMode() const { return m_blendMode; }

		/* +-----------------------------------------------+ */
		/* |                  Draw Sprite                  | */
		/* +-----------------------------------------------+ */

		void DrawSprite(const Vec2 & vPos, CStaticSprite * pSprite) {
			DrawSprite(vPos, pSprite, { 1.f, 1.f }, 0.f);
		}
		void DrawSprite(const Vec2 & vPos, CStaticSprite * pSprite, const Vec2 & vScale, float angle);

		// Alpha
		void DrawSpriteTransparent(const Vec2 & vPos, CStaticSprite * pSprite, Uint8 alpha) {
			DrawSpriteTransparent(vPos, pSprite, { 1.f, 1.f }, 0.f, alpha);
		}
		// Alpha
		void DrawSpriteTransparent(const Vec2 & vPos, CStaticSprite * pSprite, const Vec2 & vScale, float angle, Uint8 alpha);

		// Blend
		void DrawSpriteBlended(const Vec2 & vPos, CStaticSprite * pSprite, const ColorRGB & rgb) {
			DrawSpriteBlended(vPos, pSprite, { 1.f, 1.f }, 0.f, rgb);
		}
		// Blend
		void DrawSpriteBlended(const Vec2 & vPos, CStaticSprite * pSprite, const Vec2 & vScale, float angle, const ColorRGB & rgb);

		// Blend & Alpha
		void DrawSpriteBlended(const Vec2 & vPos, CStaticSprite * pSprite, const ColorRGB & rgb, Uint8 alpha) {
			DrawSpriteBlended(vPos, pSprite, { 1.f, 1.f }, 0.f, rgb, alpha);
		}
		// Blend & Alpha
		void DrawSpriteBlended(const Vec2 & vPos, CStaticSprite * pSprite, const Vec2 & vScale, float angle, const ColorRGB & rgb, Uint8 alpha);

	};

};