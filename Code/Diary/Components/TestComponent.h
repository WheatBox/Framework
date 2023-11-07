#pragma once

#include <FrameEntity/IEntityComponent.h>

class CTestComponent final : public Frame::IEntityComponent {

public:

	virtual Frame::EntityEvent::Flags GetEventFlags() override;
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override;

};