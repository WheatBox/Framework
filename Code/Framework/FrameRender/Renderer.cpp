#include <FrameRender/Renderer.h>

#include <FrameRender/ShapeRenderer.h>
#include <FrameRender/TextRenderer.h>

#include <FrameAsset/AssetsManager.h>

#include <SDL_render.h>
#include <SDL_hints.h>

namespace Frame {

	void CRenderer::Initialize(SDL_Window * sdlWindow) {
		m_sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

		m_blendMode = EBlendMode::Blend;

		SDL_SetRenderDrawBlendMode(m_sdlRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		pShapeRenderer = new CShapeRenderer {};
		pShapeRenderer->SetSdlRenderer(m_sdlRenderer);

		pTextRenderer = new CTextRenderer { & m_color, & m_alpha };
		pTextRenderer->SetSdlRenderer(m_sdlRenderer);
	}

	void CRenderer::RenderBegin() {
		SetColorAlpha(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 255);
		SDL_RenderClear(m_sdlRenderer);
	}

	void CRenderer::RenderEnd() {
		SDL_RenderPresent(m_sdlRenderer);
	}

	/* +-----------------------------------------------+ */
	/* |                Set Draw Params                | */
	/* +-----------------------------------------------+ */

	void CRenderer::SetColorAlpha(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
		m_color.Set(r, g, b);
		m_alpha = alpha;
		SDL_SetRenderDrawColor(m_sdlRenderer, r, g, b, alpha);
	}

	void CRenderer::SetBlendMode(EBlendMode blendMode) {
		m_blendMode = blendMode;
		SDL_SetRenderDrawBlendMode(m_sdlRenderer, static_cast<SDL_BlendMode>(blendMode));
	}

	/* +-----------------------------------------------+ */
	/* |                 Draw  Texture                 | */
	/* +-----------------------------------------------+ */

	void CRenderer::DrawSprite(const Vec2 & vPos, CStaticSprite * pSprite, const Vec2 & vScale, float angle) {
		SDL_FRect destRect {
			vPos.x - pSprite->GetXOffset() * vScale.x,
			vPos.y - pSprite->GetYOffset() * vScale.y,
			static_cast<float>(pSprite->GetWidth()) * vScale.x,
			static_cast<float>(pSprite->GetHeight()) * vScale.y
		};
		SDL_FPoint rotationOffset { vPos.x, vPos.y };
		SDL_RenderCopyExF(m_sdlRenderer, pSprite->GetSdlTexture(), NULL, & destRect, angle, & rotationOffset, SDL_RendererFlip::SDL_FLIP_NONE);
	}

};