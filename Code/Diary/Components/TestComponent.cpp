﻿#include "TestComponent.h"

#include <FrameEntity/IEntity.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameRender/ShapeRenderer.h>
#include <FrameRender/TextRenderer.h>
#include <FrameAsset/AssetsManager.h>

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
		m_pEntity->m_rotation += 1.f;
		
		Frame::Vec2 pos = m_pEntity->m_position;
		Frame::Vec2 size = m_pEntity->m_size;

		Frame::gRenderer->SetColor(0x81F377);
		Frame::gRenderer->m_pShapeRenderer->DrawRectangle(
			pos.x - size.x / 2,
			pos.y - size.y / 2,
			pos.x + size.x / 2,
			pos.y + size.y / 2,
			true
		);
	}
	break;
	case Frame::EntityEvent::Render:
	{
		Frame::Vec2 pos = m_pEntity->m_position;
		Frame::Vec2 size = m_pEntity->m_size;

		Frame::gRenderer->SetColor(0x8D6B94);
		Frame::gRenderer->m_pShapeRenderer->DrawRectangle(
			pos.x - size.x / 3,
			pos.y - size.y / 3,
			pos.x + size.x / 3,
			pos.y + size.y / 3,
			true
		);
	}
	break;
	}
}

void CTestComponent2::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	static bool bInited = false;
	switch(event.flag) {
	case Frame::EntityEvent::Render:
	{
		if(!bInited) {
			bInited = true;
			Frame::CFont * pFont = Frame::gAssetsManager->OpenFont("C:/Users/15599/AppData/Local/Microsoft/Windows/Fonts/智勇手书体.ttf", 32);
			Frame::gRenderer->m_pTextRenderer->SetFont(pFont);
		}

		Frame::gRenderer->SetColor(0xEEEEEE);
		Frame::gRenderer->SetAlpha(128);
		Frame::gRenderer->m_pShapeRenderer->DrawRectangle(120, 40, 400, 200, true);
		
		Frame::gRenderer->m_pTextRenderer->SetAutoWrapLength(0);
		Frame::gRenderer->m_pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Left, Frame::CFont::EVAlign::Top);
		Frame::gRenderer->m_pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->SetAlpha(255);
		Frame::gRenderer->m_pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Right, Frame::CFont::EVAlign::Bottom);
		Frame::gRenderer->m_pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->m_pTextRenderer->SetAutoWrapLength(140);
		Frame::gRenderer->m_pTextRenderer->GetFont()->SetHAlign(Frame::CFont::EHAlign::Center);
		Frame::gRenderer->m_pTextRenderer->DrawText(400, 300, "Hello, world!\n你好，世界，我在这里！", 0xFFFFFF, 255);
	}
	break;
	}
}