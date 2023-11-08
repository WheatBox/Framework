#pragma once

#include <FrameEntity/IEntityComponent.h>
#include <FrameEntity/ComponentRegister.h>

class CTestComponent final : public Frame::IEntityComponent {

public:

	virtual Frame::EntityEvent::Flags GetEventFlags() const override;
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override;

	static void Register(Frame::SComponentType<CTestComponent> type) {
		type.SetGUID("{F103ABD5-7F46-4CE6-B20C-84AE2EB9CB5B}");
	}

};

class CTestComponent2 final : public Frame::IEntityComponent {

public:

	static void Register(Frame::SComponentType<CTestComponent2> type) {
		type.SetGUID("{AAAAAAAA-7F46-4CE6-B20C-84AE2EB9CB5B}");
	}

	virtual Frame::EntityEvent::Flags GetEventFlags() const override {
		return Frame::EntityEvent::EFlag::Render;
	}
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override;

};

class CTestComponent3 final : public Frame::IEntityComponent {

public:

	static void Register(Frame::SComponentType<CTestComponent3> type) {
		type.SetGUID("{BBBBBBBB-7F46-4CE6-B20C-84AE2EB9CB5B}");
	}

	virtual Frame::EntityEvent::Flags GetEventFlags() const override {
		return Frame::EntityEvent::EFlag::Nothing;
	}
	virtual void ProcessEvent(const Frame::EntityEvent::SEvent & event) override {event;}

};
