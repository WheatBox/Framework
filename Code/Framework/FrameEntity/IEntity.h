#pragma once

#include <FrameCore/Globals.h>
#include <FrameMath/Vector2.h>
#include <FrameUtility/GUID.h>

#include <unordered_map>
#include <string>

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

			m_components.insert(std::pair<GUID, IEntityComponent *> { SComponentType<ComponentType>::GetGUID(), pComponent });
			
			return pComponent;
		}

		template<typename ComponentType>
		ComponentType * GetComponent() {
			auto it = m_components.find(SComponentType<ComponentType>::GetGUID());
			if(it != m_components.end()) {
				return static_cast<ComponentType *>(it->second);
			}
			return nullptr;
		}

		template<typename ComponentType>
		ComponentType * GetOrCreateComponent() {
			if(ComponentType * pComponent = GetComponent<ComponentType>()) {
				return pComponent;
			}
			return CreateComponent<ComponentType>();
		}

		template<typename ComponentType>
		void RemoveComponent() {
			auto it = m_components.find(SComponentType<ComponentType>::GetGUID());
			if(it != m_components.end()) {
				gEntitySystem->ComponentRemoveFromProcessors(it->second);
				delete static_cast<ComponentType *>(it->second);
				m_components.erase(it);
			}
		}

	private:
		std::unordered_map<GUID, IEntityComponent *> m_components;
		
		void InitializeComponent(IEntityComponent * pComponent);
		void ComponentAddIntoProcessors(IEntityComponent * pComponent);

	};

};