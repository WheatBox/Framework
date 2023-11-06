#include "DiaryApplication.h"

#include <SDL_events.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include "Entities/TestEntity.h"

void CDiaryApplication::ProcessSdlEvent(SDL_Event & sdlEvent) {
	switch(sdlEvent.type) {
	case SDL_QUIT:
		m_quit = true;
		break;
	}
}

bool b = false;
void CDiaryApplication::MainLoopPriority() {
	if(!b) {
		b = true;
		Frame::IEntity * pEntity = Frame::gEntitySystem->SpawnEntity<CTestEntity>();
		pEntity->m_position = { 400, 300 };
		pEntity->m_size = { 200, 150 };
	}
}
