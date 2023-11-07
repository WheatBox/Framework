#pragma once

#include <FrameCore/Globals.h>
#include <FrameMath/Vector2.h>

#include <unordered_set>

namespace Frame {
	
	typedef unsigned int EntityId;

	struct IEntityComponent;

	struct IEntity {
		
		const EntityId m_id;

		IEntity() = delete;
		IEntity(EntityId id)
			: m_id(id)
		{}
		virtual ~IEntity() = default;

		EntityId GetId() const { return m_id; }

		Vec2 m_position { 0.f };
		Vec2 m_size { 0.f };
		Vec2 m_offset { 0.f };

		// 角度 | Degree
		float m_rotation = 0.f;

		// 主要用以表示遮挡关系（渲染顺序）
		// 数值越小，离镜头越近，渲染越晚
		// Mainly used to represent occlusion relationships (rendering order)
		// The smaller the value, the closer it is to the camera, and the later it renders
		int m_zDepth = 0;

		template<typename ComponentType>
		ComponentType * CreateComponent() {
			ComponentType * pComponent = new ComponentType {};
			InitializeComponent(pComponent);
			ComponentAddIntoProcessors(pComponent);
			m_components.insert(pComponent);
			return pComponent;
		}

		template<typename ComponentType>
		ComponentType * GetComponent() {
			// TODO - Reflection
			return nullptr;
		}

		template<typename ComponentType>
		ComponentType * GetOrCreateComponent() {
			if(ComponentType * pComponent = GetComponent<ComponentType>()) {
				return pComponent;
			}
			return CreateComponent<ComponentType>();
		}

		void RemoveComponent(IEntityComponent * pComponent);

	private:
		std::unordered_set<IEntityComponent *> m_components;
		
		void InitializeComponent(IEntityComponent * pComponent);
		void ComponentAddIntoProcessors(IEntityComponent * pComponent);

	};

};