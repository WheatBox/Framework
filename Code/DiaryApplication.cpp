#include "DiaryApplication.h"

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Diary/Components/TestComponent.h"

#include <iostream>

void CDiaryApplication::Initialize(int argc, char ** argv) {
	argc, argv;

	SetVSync(true);

	if(Frame::CEntity * pEntity = Frame::gEntitySystem->SpawnEntity()) {
		pEntity->SetPosition({ 400, 300 });

		printf("%lld\n", Frame::SComponentType<CTestComponent>::GetGUID().high);
		printf("%lld\n", Frame::SComponentType<CTestComponent2>::GetGUID().high);
		printf("%lld\n", Frame::SComponentType<CTestComponent3>::GetGUID().high);

		printf("\n---------------------------------\n");
		auto show = [pEntity]() { printf("%p %p %p\n", pEntity->GetComponent<CTestComponent>(), pEntity->GetComponent<CTestComponent2>(), pEntity->GetComponent<CTestComponent3>()); };
		show();
		pEntity->CreateComponent<CTestComponent>()->SetSize({ 200, 150 });
		pEntity->CreateComponent<CTestComponent2>();
		show();
		pEntity->RemoveComponent<CTestComponent>();
		show();
	}

	Frame::gRenderer->SetBackgroundColor(0x00004F);
	//Frame::gRenderer->SetBackgroundColor(0xFFFFFF);
}

/*
#include <SDL_events.h>
#include <SDL_log.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Diary/Components/TestComponent.h"

void CDiaryApplication::Initialize() {

	SetMaxFPS(30);

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

	Frame::gRenderer->SetBackgroundColor(0x00004F);

}
*/