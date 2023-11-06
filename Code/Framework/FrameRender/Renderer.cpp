#include <FrameRender/Renderer.h>

#include <SDL_render.h>
#include <SDL_hints.h>

namespace Frame {

	void CRenderer::Initialize(SDL_Window * sdlWindow) {
		m_sdlWindow = sdlWindow;
		m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, 0);

		SDL_SetRenderDrawBlendMode(m_sdlRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	}

	void CRenderer::RenderBegin() {
		SetDrawColorAlpha(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 255);
		SDL_RenderClear(m_sdlRenderer);
	}

	void CRenderer::RenderEnd() {
		SDL_RenderPresent(m_sdlRenderer);
	}

	/* +-----------------------------------------------+ */
	/* |                Set Draw Params                | */
	/* +-----------------------------------------------+ */

	void CRenderer::SetDrawColorAlpha(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
		m_color.Set(r, g, b);
		m_alpha = alpha;
		SDL_SetRenderDrawColor(m_sdlRenderer, r, g, b, alpha);
	}

	void CRenderer::SetDrawColorAlpha(int rgb, Uint8 alpha) {
		m_color = rgb;
		m_alpha = alpha;
		SDL_SetRenderDrawColor(m_sdlRenderer, m_color.r, m_color.g, m_color.b, alpha);
	}

	void CRenderer::SetDrawBlendMode(EBlendMode blendModes) {
		SDL_SetRenderDrawBlendMode(m_sdlRenderer, static_cast<SDL_BlendMode>(blendModes));
	}

	/* +-----------------------------------------------+ */
	/* |               Draw Basic Shapes               | */
	/* +-----------------------------------------------+ */

	void CRenderer::DrawPixel(int x, int y) {
		SDL_RenderDrawPoint(m_sdlRenderer, x, y);
	}
	
	void CRenderer::DrawPixel(float x, float y) {
		SDL_RenderDrawPointF(m_sdlRenderer, x, y);
	}

	void CRenderer::DrawLine(int x1, int y1, int x2, int y2) {
		SDL_RenderDrawLine(m_sdlRenderer, x1, y1, x2, y2);
	}

	void CRenderer::DrawLine(float x1, float y1, float x2, float y2) {
		SDL_RenderDrawLineF(m_sdlRenderer, x1, y1, x2, y2);
	}

	void CRenderer::DrawRectangle(int x1, int y1, int x2, int y2, bool fill) {
		SDL_Rect rect { x1, y1, x2 - x1, y2 - y1 };
		(fill ? SDL_RenderFillRect : SDL_RenderDrawRect)(m_sdlRenderer, & rect);
	}

	void CRenderer::DrawRectangle(float x1, float y1, float x2, float y2, bool fill) {
		SDL_FRect rect { x1, y1, x2 - x1, y2 - y1 };
		(fill ? SDL_RenderFillRectF : SDL_RenderDrawRectF)(m_sdlRenderer, & rect);
	}

	void CRenderer::DrawRectangleWH(int x, int y, int w, int h, bool fill) {
		SDL_Rect rect { x, y, w, h };
		(fill ? SDL_RenderFillRect : SDL_RenderDrawRect)(m_sdlRenderer, & rect);
	}

	void CRenderer::DrawRectangleWH(float x, float y, float w, float h, bool fill) {
		SDL_FRect rect { x, y, w, h };
		(fill ? SDL_RenderFillRectF : SDL_RenderDrawRectF)(m_sdlRenderer, & rect);
	}

};