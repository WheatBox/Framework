#pragma once

#include <FrameEntity/IEntity.h>

class CTestEntity final : public Frame::IEntity {

public:
	CTestEntity(Frame::EntityId id)
		: Frame::IEntity(id)
	{}

	virtual Frame::EntityEvent::Flags GetEventFlags() override;
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override;

};