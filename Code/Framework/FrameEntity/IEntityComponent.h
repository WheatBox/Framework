#pragma once

#include <FrameEntity/EntityEvent.h>

namespace Frame {

	struct IEntity;

	struct IEntityComponent {

		IEntityComponent() = default;
		virtual ~IEntityComponent() = default;

		void Construct(IEntity * pEntity) {
			m_pEntity = pEntity;
		}

		// Example:
		//	virtual EntityEvent::Flags GetEventFlags() override {
		//		return EntityEvent::EFlag::Nothing
		//			| EntityEvent::EFlag::Initialize
		//			| EntityEvent::EFlag::Update
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

		IEntity * GetEntity() const {
			return m_pEntity;
		}
	protected:
		IEntity * m_pEntity;

	};

};