#pragma once

#include <FrameMath/Vector2.h>
#include <FrameEntity/EntityEvent.h>

#include <unordered_map>

namespace Frame {
	
	typedef unsigned int EntityId;

	struct IEntity {

	private:
		EntityId m_id;

	public:

		IEntity() = delete;
		IEntity(int id)
			: m_id(id)
		{}
		virtual ~IEntity() {};

		EntityId GetId() const { return m_id; }
		
		// Example:
		//	virtual EntityEvent::Flags GetEventFlags() override {
		//		return EntityEvent::EFlag::Nothing
		//			| EntityEvent::EFlag::Initialize
		//			| EntityEvent::EFlag::Update
		//			...;
		//	}
		virtual EntityEvent::Flags GetEventFlags() = 0;

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

		Vec2 m_position { 0.f };
		Vec2 m_size { 0.f };
		Vec2 m_offset { 0.f };

		// 角度 | Degree
		float m_rotation = 0.f;

		// 主要用以表示遮挡关系（渲染顺序）
		// 数值越小，离镜头越近，渲染越晚
		// Mainly used to represent occlusion relationships (rendering order)
		// The smaller the value, the closer it is to the camera, and the later it renders
		int z = 0;

	};

};