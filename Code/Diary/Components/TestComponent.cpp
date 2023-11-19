#include "TestComponent.h"

#include <FrameEntity/Entity.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameRender/ShapeRenderer.h>
#include <FrameRender/TextRenderer.h>
#include <FrameAsset/AssetsManager.h>
#include <FrameInput/InputManager.h>

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
		Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 2,
			pos.y - m_size.y / 2,
			pos.x + m_size.x / 2,
			pos.y + m_size.y / 2,
			true
		);
	}
	break;
	case Frame::EntityEvent::Render:
	{
		Frame::Vec2 pos = m_pEntity->GetPosition();

		Frame::gRenderer->SetColor(0x8D6B94);
		Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 3,
			pos.y - m_size.y / 3,
			pos.x + m_size.x / 3,
			pos.y + m_size.y / 3,
			true
		);
	}
	break;
	}
}
#include <SDL.h>
void CTestComponent2::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	static bool bInited = false;
	static float angle = 0.f;
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		float frameTime = event.params[0].f;

		m_strFrameTime = "Test\n测试\nFrame time: " + std::to_string(frameTime) + "\nFps: " + std::to_string(int(1 / frameTime));
		
		angle += frameTime * 360; // => 360°/s
	}
	break;
	case Frame::EntityEvent::Render:
	{
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
		SDL_Log("%d %d %d %d",
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_A),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_S),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_D),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_LShift)
		);
	}
	break;
	}
}