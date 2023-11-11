#pragma once

#include <FrameRender/BasicRenderingTypes.h>

namespace Frame {

	struct IRenderer {

		IRenderer() = default;
		IRenderer(SDL_Renderer * sdlRenderer)
			: m_sdlRenderer(sdlRenderer)
		{};
		virtual ~IRenderer() = default;

		void SetSdlRenderer(SDL_Renderer * sdlRenderer) {
			m_sdlRenderer = sdlRenderer;
		}

	protected:
		SDL_Renderer * m_sdlRenderer;

	};

}