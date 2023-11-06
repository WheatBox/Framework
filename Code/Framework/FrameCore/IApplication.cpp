#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameEntity/EntityEventProcessor.h>

#include <SDL.h>

namespace Frame {

	bool IApplication::InitializeWindow(const char * title, int windowWidth, int windowHeight) {
		
		SDL_InitSubSystem(SDL_INIT_VIDEO);

		m_sdlWindow = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowWidth, windowHeight,
			SDL_WindowFlags::SDL_WINDOW_RESIZABLE
		);

		gRenderer->Initialize(m_sdlWindow);

		return m_sdlWindow != NULL;
	}

	void IApplication::Run() {

		SDL_Event sdlEvent;
		while(!m_quit) {
			while(SDL_PollEvent(& sdlEvent)) {
				ProcessSdlEvent(sdlEvent);
			}

			MainLoopPriority();
			/* ------------- Main Loop ------------- */
			
			gEntitySystem->ProcessUpdateEvent();
			
			/* ------------------------------------- */
			MainLoopLast();

			gRenderer->RenderEnd();
		}

	}

	void IApplication::ProcessSdlEvent(SDL_Event & sdlEvent) {
		switch(sdlEvent.type) {
		case SDL_QUIT:
			m_quit = true;
			break;
		}
	}

}