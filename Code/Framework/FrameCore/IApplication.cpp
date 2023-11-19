#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameEntity/EntityEventProcessor.h>
#include <FrameInput/InputManager.h>

#include <thread>

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

		Initialize();

		SDL_Event sdlEvent;
		while(!m_quit) {
			static std::chrono::steady_clock::time_point prevTimePoint = std::chrono::steady_clock::now(), beforeLoopTimePoint;
			static float frameTime = 0.f;

			beforeLoopTimePoint = std::chrono::steady_clock::now();

			frameTime = std::chrono::duration<float>(beforeLoopTimePoint - prevTimePoint).count();
			prevTimePoint = beforeLoopTimePoint;

			while(SDL_PollEvent(& sdlEvent)) {
				ProcessSdlEvent(sdlEvent);
			}
			gInputManager->pKeyboard->ProcessChanges();

			gRenderer->RenderBegin();

			MainLoopPriority();
			/* ------------- Main Loop ------------- */
			
			gEntitySystem->ProcessUpdateEvent(frameTime);

			gEntitySystem->ProcessRenderEvent();
			
			/* ------------------------------------- */
			MainLoopLast();

			gRenderer->RenderEnd();
			
			if(m_maxFPS != 0) {
				std::this_thread::sleep_until(beforeLoopTimePoint + m_maxFrameDelay);
			}
		}

	}

	void IApplication::ProcessSdlEvent(SDL_Event & sdlEvent) {
		switch(sdlEvent.type) {
		case SDL_EventType::SDL_QUIT:
			m_quit = true;
			break;
		case SDL_EventType::SDL_KEYDOWN:
			 SDL_Log("DOWN %d | %s", sdlEvent.key.keysym.sym, SDL_GetKeyName(sdlEvent.key.keysym.sym));
			gInputManager->pKeyboard->SetInputState(static_cast<EInputKeyId>(sdlEvent.key.keysym.sym), EInputState::eIS_Press);
			break;
		case SDL_EventType::SDL_KEYUP:
			gInputManager->pKeyboard->SetInputState(static_cast<EInputKeyId>(sdlEvent.key.keysym.sym), EInputState::eIS_Release);
			break;
		}
	}

}