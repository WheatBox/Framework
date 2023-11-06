#include "TestEntity.h"

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>

Frame::EntityEvent::Flags CTestEntity::GetEventFlags() {
	return Frame::EntityEvent::EFlag::Update
		 | Frame::EntityEvent::EFlag::Render
		;
}

void CTestEntity::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		m_rotation += 1.f;
		Frame::gRenderer->SetDrawColor(0x81F377);
		Frame::gRenderer->DrawRectangle(
			m_position.x - m_size.x / 2,
			m_position.y - m_size.y / 2,
			m_position.x + m_size.x / 2,
			m_position.y + m_size.y / 2,
			true
		);
	}
	break;
	case Frame::EntityEvent::Render:
	{
		Frame::gRenderer->SetDrawColor(0x81F377);
		Frame::gRenderer->DrawRectangle(
			m_position.x - m_size.x / 2,
			m_position.y - m_size.y / 2,
			m_position.x + m_size.x / 2,
			m_position.y + m_size.y / 2
		);
	}
	break;
	}
}