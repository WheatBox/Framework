#include <FrameRender/ShapeRenderer.h>

#include <SDL_render.h>

namespace Frame {

	/* +-----------------------------------------------+ */
	/* |               Draw Basic Shapes               | */
	/* +-----------------------------------------------+ */

	void CShapeRenderer::DrawPixel(int x, int y) {
		SDL_RenderDrawPoint(m_sdlRenderer, x, y);
	}

	void CShapeRenderer::DrawPixel(float x, float y) {
		SDL_RenderDrawPointF(m_sdlRenderer, x, y);
	}

	void CShapeRenderer::DrawLine(int x1, int y1, int x2, int y2) {
		SDL_RenderDrawLine(m_sdlRenderer, x1, y1, x2, y2);
	}

	void CShapeRenderer::DrawLine(float x1, float y1, float x2, float y2) {
		SDL_RenderDrawLineF(m_sdlRenderer, x1, y1, x2, y2);
	}

	void CShapeRenderer::DrawRectangle(int x1, int y1, int x2, int y2, bool fill) {
		SDL_Rect rect { x1, y1, x2 - x1, y2 - y1 };
		(fill ? SDL_RenderFillRect : SDL_RenderDrawRect)(m_sdlRenderer, & rect);
	}

	void CShapeRenderer::DrawRectangle(float x1, float y1, float x2, float y2, bool fill) {
		SDL_FRect rect { x1, y1, x2 - x1, y2 - y1 };
		(fill ? SDL_RenderFillRectF : SDL_RenderDrawRectF)(m_sdlRenderer, & rect);
	}

	void CShapeRenderer::DrawRectangleWH(int x, int y, int w, int h, bool fill) {
		SDL_Rect rect { x, y, w, h };
		(fill ? SDL_RenderFillRect : SDL_RenderDrawRect)(m_sdlRenderer, & rect);
	}

	void CShapeRenderer::DrawRectangleWH(float x, float y, float w, float h, bool fill) {
		SDL_FRect rect { x, y, w, h };
		(fill ? SDL_RenderFillRectF : SDL_RenderDrawRectF)(m_sdlRenderer, & rect);
	}

}