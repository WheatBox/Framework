#pragma once

#include <FrameMath/ColorMath.h>
#include <SDL_blendmode.h>

struct SDL_Renderer;
struct SDL_Window;

namespace Frame {

	class CRenderer {
	public:
		CRenderer() = default;
		virtual ~CRenderer() = default;

		void Initialize(SDL_Window * sdlWindow);

	private:
		SDL_Renderer * m_sdlRenderer = nullptr;
		SDL_Window * m_sdlWindow = nullptr;

		ColorRGB m_color { 255, 255, 255 };
		Uint8 m_alpha = 255;

	public:
		ColorRGB m_backgroundColor { 0, 0, 0 };

	public:
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

	public:

		void RenderBegin();
		void RenderEnd();

		/* +-----------------------------------------------+ */
		/* |                Set Draw Params                | */
		/* +-----------------------------------------------+ */

		inline void SetDrawColor(Uint8 r, Uint8 g, Uint8 b) {
			SetDrawColorAlpha(r, g, b, m_alpha);
		}
		inline void SetDrawColor(int rgb) {
			SetDrawColorAlpha(rgb, m_alpha);
		}

		inline void SetDrawAlpha(Uint8 alpha) {
			SetDrawColorAlpha(m_color.r, m_color.g, m_color.b, alpha);
		}

		void SetDrawColorAlpha(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
		void SetDrawColorAlpha(int rgb, Uint8 alpha);

		void SetDrawBlendMode(EBlendMode blendModes);

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawPixel(int x, int y);
		void DrawPixel(float x, float y);

		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawRectangle(int x1, int y1, int x2, int y2, bool fill = false);
		void DrawRectangle(float x1, float y1, float x2, float y2, bool fill = false);
		void DrawRectangleWH(int x, int y, int w, int h, bool fill = false);
		void DrawRectangleWH(float x, float y, float w, float h, bool fill = false);
		
	};

};