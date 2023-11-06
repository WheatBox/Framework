#pragma once

#include <FrameEntity/IEntity.h>

class CTestEntity final : public Frame::IEntity {

public:

	virtual Frame::EntityEvent::Flags GetEventFlags() override;
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override;

};