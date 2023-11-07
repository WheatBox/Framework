#include "DiaryApplication.h"

#include <SDL_events.h>

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
			
			pEntity->CreateComponent<CTestComponent>();
		}
		
		Frame::gRenderer->m_backgroundColor = 0x00004F;
	}
}
