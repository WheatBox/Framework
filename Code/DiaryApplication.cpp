#include "DiaryApplication.h"

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Diary/Components/TestComponent.h"

#include <iostream>

void CDiaryApplication::Initialize() {
	//SetVSync(true);
	SetVSync(false);
	SetMaxFPS(60);

	if(Frame::CEntity * pEntity = Frame::gEntitySystem->SpawnEntity()) {
		pEntity->SetPosition({ 400, 300 });

		printf("%lld\n", Frame::SComponentType<CTestComponent>::config.GetGUID().high);
		printf("%lld\n", Frame::SComponentType<CTestComponent2>::config.GetGUID().high);
		printf("%lld\n", Frame::SComponentType<CTestComponent3>::config.GetGUID().high);

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
