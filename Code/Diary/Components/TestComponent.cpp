#include "TestComponent.h"

#include <FrameEntity/Entity.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
//#include <FrameInput/InputManager.h>

#include <FrameAsset/Sprite.h>
#include <FrameAsset/Font.h>

REGISTER_ENTITY_COMPONENT(, CTestComponent);
REGISTER_ENTITY_COMPONENT(, CTestComponent2);
REGISTER_ENTITY_COMPONENT(, CTestComponent3);

Frame::EntityEvent::Flags CTestComponent::GetEventFlags() const {
	return Frame::EntityEvent::EFlag::Update
		 | Frame::EntityEvent::EFlag::Render
		;
}

void CTestComponent::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		m_pEntity->Rotate(1.f);
		
		Frame::Vec2 pos = m_pEntity->GetPosition();

		Frame::gRenderer->SetColor(0x81F377);
		/*Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 2,
			pos.y - m_size.y / 2,
			pos.x + m_size.x / 2,
			pos.y + m_size.y / 2,
			true
		);*/
	}
	break;
	case Frame::EntityEvent::Render:
	{
		Frame::Vec2 pos = m_pEntity->GetPosition();

		Frame::gRenderer->SetColor(0x8D6B94);
		/*Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 3,
			pos.y - m_size.y / 3,
			pos.x + m_size.x / 3,
			pos.y + m_size.y / 3,
			true
		);*/
	}
	break;
	}
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <FrameUtility/UTF8Utils.h>
void CTestComponent2::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	static bool bInited = false;
	static float angle = 0.f;

	static Frame::CStaticSprite * pSprite = nullptr;
	static Frame::CFont * pFont = nullptr;
	static Frame::CFont * pFont2 = nullptr;
	static Frame::CFont * pFont3 = nullptr;
	
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		float frameTime = event.params[0].f;

		m_strFrameTime = "Test\n测试\nFrame time: " + std::to_string(frameTime) + "\nFps: " + std::to_string(int(1 / frameTime));
		
		//angle += frameTime * 360; // => 360°/s
		angle += frameTime * 360 / 5.f;
	}
	break;
	case Frame::EntityEvent::Render:
	{
		if(!bInited) {
			bInited = true;
			pSprite = new Frame::CStaticSprite { "./Assets/spr_t.bmp" };
			pSprite->SetOffset({ static_cast<float>(pSprite->GetWidth()) / 2.f, static_cast<float>(pSprite->GetHeight()) / 2.f });

			pFont = new Frame::CFont { "C:/Windows/Fonts/STZHONGS.TTF", 32.f };
			pFont2 = new Frame::CFont { "C:/Windows/Fonts/STZHONGS.TTF", 32.5f };
			pFont3 = new Frame::CFont { "C:/Windows/Fonts/STZHONGS.TTF", 33.f };
			Frame::gRenderer->pTextRenderer->SetFont(pFont);
		}

#if 1
		//Frame::gRenderer->pSpriteShader->Use();
		//Frame::gRenderer->pSpriteShader->SetUniformInt("u_BaseTexture", 0);

		Frame::gRenderer->SetAlpha(.5f);
		Frame::gRenderer->DrawSprite(pSprite, { 340.f , 400.f }, { 0.7f }, angle);
		Frame::gRenderer->DrawSpriteBlended(pSprite, { 400.f , 300.f },
			0xFF0000, 1.f, 0x00FF00, 1.f,
			0x0000FF, 0.f, 0xFFFF00, 0.f,
			1.2f, -angle
		);

		Frame::gRenderer->SetColorAlpha(0xFFFFFF, .4f);
		Frame::gRenderer->pTextRenderer->DrawText("Hello, world! 你好，世界！", { 20, 20 });
		Frame::gRenderer->pTextRenderer->DrawText("The quick brown fox jumps over the lazy dog.", { 20, 60 });
		Frame::gRenderer->pTextRenderer->SetFont(pFont);
		Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		Frame::gRenderer->SetColorAlpha(0xFFFFFF, .7f);
		Frame::gRenderer->pTextRenderer->SetFont(pFont2);
		Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		Frame::gRenderer->SetColorAlpha(0xFFFFFF, 1.f);
		Frame::gRenderer->pTextRenderer->SetFont(pFont3);
		Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		//constexpr UnicodeChar uni = Frame::UTF8Utils::ToUnicodeCharacter("😀");

		Frame::gRenderer->SetColorAlpha(0xFFFFFF, 1.f);
		Frame::gRenderer->pShapeRenderer->DrawPixelColorBlended({ 100.f, 300.f }, 0x00FF00, 32.f);

		Frame::gRenderer->pShapeRenderer->DrawLineBlended({ 200.f, 200.f }, { 700.f, 500.f }, 0x00FF00, 1.f, 0x0000FF, 0.f, 16.f);
		Frame::gRenderer->pShapeRenderer->DrawLineAlphaBlended({ 200.f, 500.f }, { 700.f, 500.f }, 1.f, 0.f, 16.f);
		
		Frame::gRenderer->pShapeRenderer->DrawQuadrilateralBlended(
			{ 100.f, 300.f }, { 170.f, 280.f },
			{ 120.f, 400.f }, { 210.f, 360.f },
			0xFF0000, 1.f, 0x00FF00, .5f,
			0x0000FF, .5f, 0xFFFF00, 0.f,
			0.f
		);
		
		Frame::gRenderer->pShapeRenderer->DrawTriangle({ 100, 200 }, { 400, 300 }, { 200, 250 });
		Frame::gRenderer->pShapeRenderer->DrawTriangle({ 100, 400 }, { 200, 450 }, { 400, 500 });
#else 
		for(int i = 0; i < 100; i++) Frame::gRenderer->DrawSpriteBlended(pSprite, { 400 , 300 }, 0xFFFFFF, 0.5f, { 1.f }, angle);
#endif
		/*
		if(!bInited) {
			bInited = true;
			Frame::CFont * pFont = Frame::gAssetsManager->OpenFont("C:/Windows/Fonts/STZHONGS.TTF", 32);
			Frame::gRenderer->pTextRenderer->SetFont(pFont);
		}

		Frame::gRenderer->SetColor(0xEEEEEE);
		Frame::gRenderer->SetAlpha(128);
		Frame::gRenderer->pShapeRenderer->DrawRectangle(120, 40, 400, 200, true);
		
		Frame::gRenderer->pTextRenderer->SetAutoWrapLength(0);
		Frame::gRenderer->pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Left, Frame::CFont::EVAlign::Top);
		Frame::gRenderer->pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->SetAlpha(255);
		Frame::gRenderer->pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Right, Frame::CFont::EVAlign::Bottom);
		Frame::gRenderer->pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->pTextRenderer->SetAutoWrapLength(160);
		Frame::gRenderer->pTextRenderer->GetFont()->SetHAlign(Frame::CFont::EHAlign::Center);
		Frame::gRenderer->pTextRenderer->DrawText(400, 300, "Hello, world!\n你好，世界，我在这里！", 0xFFFFFF, 255);

		Frame::gRenderer->pTextRenderer->GetFont()->SetHAlign(Frame::CFont::EHAlign::Left);
		Frame::CStaticSprite * pSprite = Frame::gRenderer->pTextRenderer->DrawTextAsSprite(m_strFrameTime.c_str(), 0xFFFFFF, 255);
		pSprite->SetOffset({ pSprite->GetWidth() / 2.f, static_cast<float>(pSprite->GetHeight()) });
		// pSprite->SetAlphaBlend(128);
		// pSprite->SetColorBlend(0xFF00FF);
		Frame::gRenderer->DrawSpriteBlended({ 400, 300 }, pSprite, { 0.5f }, angle, 0xFF00FF, 128);
		Frame::gAssetsManager->DestroyStaticSprite(pSprite);
		
		if( Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_A) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_S) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_D) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_LShift)
			)
		printf("%d %d %d %d\n",
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_A),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_S),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_D),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_LShift)
		);*/
	}
	break;
	}
}