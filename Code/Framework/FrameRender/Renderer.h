#pragma once

#include <FrameMath/ColorMath.h>

#include <SDL_blendmode.h>

struct SDL_Renderer;
struct SDL_Window;

namespace Frame {

	class CShapeRenderer;
	class CTextRenderer;

	struct STexture;

	class CRenderer {

	public:
		CRenderer() = default;
		virtual ~CRenderer() = default;

		void Initialize(SDL_Window * sdlWindow);

		SDL_Renderer * GetSdlRenderer() const {
			return m_sdlRenderer;
		}

		CShapeRenderer * m_pShapeRenderer = nullptr;
		CTextRenderer * m_pTextRenderer = nullptr;

		ColorRGB m_backgroundColor { 0, 0, 0 };

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

		ColorRGB GetColor() const { return m_color; }
		Uint8 GetAlpha() const { return m_alpha; }

		void SetBlendMode(EBlendMode blendMode);

		EBlendMode GetBlendMode() const { return m_blendMode; }

		/* +-----------------------------------------------+ */
		/* |                 Draw  Texture                 | */
		/* +-----------------------------------------------+ */

		void DrawTexture(int x, int y, STexture * pTexture);

	};

};