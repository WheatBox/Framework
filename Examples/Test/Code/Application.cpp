#include "Application.h"

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameRender/Renderer.h>

#include "Components/TestComponent.h"

#include <iostream>
#include <sstream>
#include <iomanip>

void CApplication::Initialize() {
	//SetVSync(true);
	Frame::SetVSync(false);
	Frame::SetMaxFPS(60);
	//Frame::SetMaxFPS(400);

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

	const auto GUIDGenTest = []() {
		Frame::GUID guid = Frame::GUID::Generate();
		
		std::ostringstream oss;
		oss << std::uppercase << std::hex << std::setfill('0');

		unsigned char bytes[16];
		for (int i = 0; i < 8; i++) {
			bytes[7 - i] = static_cast<unsigned char>(guid.high >> (i * 8));
			bytes[15 - i] = static_cast<unsigned char>(guid.low >> (i * 8));
		}

		oss << '{';
		for (int i = 0; i < 16; i++) {
			oss << std::setw(2) << static_cast<int>(bytes[i]);
			if(i == 3 || i == 5 || i == 7 || i == 9) {
				oss << '-';
			}
		}
		oss << '}';

		std::cout << oss.str() << std::endl;
		};
	for(int i = 0; i < 10; i++) {
		GUIDGenTest();
	}

	Frame::gRenderer->SetBackgroundColor(0x00004F);
	//Frame::gRenderer->SetBackgroundColor(0xFFFFFF);
}
