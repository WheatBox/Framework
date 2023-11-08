#include "TestComponent.h"

#include <FrameEntity/IEntity.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>

REGISTER_ENTITY_COMPONENT(CTestComponent);
REGISTER_ENTITY_COMPONENT(CTestComponent2);
REGISTER_ENTITY_COMPONENT(CTestComponent3);

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

		Frame::gRenderer->SetDrawColor(0x81F377);
		Frame::gRenderer->DrawRectangle(
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

		Frame::gRenderer->SetDrawColor(0x8D6B94);
		Frame::gRenderer->DrawRectangle(
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
	switch(event.flag) {
	case Frame::EntityEvent::Render:
	{
		Frame::gRenderer->SetDrawColor(0xEEEEEE);
		Frame::gRenderer->DrawRectangle(120, 40, 400, 200, true);
	}
	break;
	}
}