#include "DiaryApplication.h"

#include <SDL_events.h>
#include <SDL.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Diary/Components/TestComponent.h"

void CDiaryApplication::ProcessSdlEvent(SDL_Event & sdlEvent) {
	switch(sdlEvent.type) {
	case SDL_QUIT:
		m_quit = true;
		break;
	}
}

void CDiaryApplication::MainLoopPriority() {
	static bool b = false;
	if(!b) {
		b = true;
		
		if(Frame::IEntity * pEntity = Frame::gEntitySystem->SpawnEntity()) {
			pEntity->m_position = { 400, 300 };
			pEntity->m_size = { 200, 150 };

			SDL_Log("%lld", Frame::SComponentType<CTestComponent>::GetGUID().high);
			SDL_Log("%lld", Frame::SComponentType<CTestComponent2>::GetGUID().high);
			SDL_Log("%lld", Frame::SComponentType<CTestComponent3>::GetGUID().high);
			
			SDL_Log("---------------------------------");
			auto show = [pEntity]() { SDL_Log("%p %p %p", pEntity->GetComponent<CTestComponent>(), pEntity->GetComponent<CTestComponent2>(), pEntity->GetComponent<CTestComponent3>()); };
			show();
			pEntity->CreateComponent<CTestComponent>();
			pEntity->CreateComponent<CTestComponent2>();
			show();
			pEntity->RemoveComponent<CTestComponent>();
			show();

		}
		
		Frame::gRenderer->m_backgroundColor = 0x00004F;
	}
}
