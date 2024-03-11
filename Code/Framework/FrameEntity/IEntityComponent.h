#pragma once

#include <FrameEntity/EntityEvent.h>

namespace Frame {

	class CEntity;

	struct IEntityComponent {

		IEntityComponent() = default;
		virtual ~IEntityComponent() = default;

		void Construct(CEntity * pEntity) {
			m_pEntity = pEntity;
		}
		
		// After construction
		virtual void Initialize() {}

		// Before destruction
		virtual void OnShutDown() {}

		// Example:
		//	virtual EntityEvent::Flags GetEventFlags() const override {
		//		return EntityEvent::EFlag::Nothing
		//			| EntityEvent::EFlag::Update
		//			| EntityEvent::EFlag::Render
		//			...;
		//	}
		virtual EntityEvent::Flags GetEventFlags() const = 0;

		// Example:
		//	virtual void ProcessEvent(const EntityEvent::SEvent & event) override {
		//		switch(event.flag) {
		//		case EntityEvent::EFlag::Nothing:
		//		{
		//			// 没啥，这只是一个样例而已
		//			// Nothing, this is just a example
		//		}
		//		break;
		//		}
		//	}
		virtual void ProcessEvent(const EntityEvent::SEvent & event) = 0;

		CEntity * GetEntity() const {
			return m_pEntity;
		}
	protected:
		CEntity * m_pEntity = nullptr;

	};

};

#include <FrameEntity/ComponentRegister.h>