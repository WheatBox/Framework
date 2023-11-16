﻿#include "DiaryApplication.h"

#include <SDL_events.h>
#include <SDL_log.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Diary/Components/TestComponent.h"

void CDiaryApplication::MainLoopPriority() {
	static bool b = false;
	if(!b) {
		b = true;
		
		if(Frame::CEntity * pEntity = Frame::gEntitySystem->SpawnEntity()) {
			pEntity->SetPosition({ 400, 300 });

			SDL_Log("%lld", Frame::SComponentType<CTestComponent>::GetGUID().high);
			SDL_Log("%lld", Frame::SComponentType<CTestComponent2>::GetGUID().high);
			SDL_Log("%lld", Frame::SComponentType<CTestComponent3>::GetGUID().high);
			
			SDL_Log("---------------------------------");
			auto show = [pEntity]() { SDL_Log("%p %p %p", pEntity->GetComponent<CTestComponent>(), pEntity->GetComponent<CTestComponent2>(), pEntity->GetComponent<CTestComponent3>()); };
			show();
			pEntity->CreateComponent<CTestComponent>()->SetSize({ 200, 150 });
			pEntity->CreateComponent<CTestComponent2>();
			show();
			pEntity->RemoveComponent<CTestComponent>();
			show();

		}
		
		Frame::gRenderer->m_backgroundColor = 0x00004F;
	}
}
