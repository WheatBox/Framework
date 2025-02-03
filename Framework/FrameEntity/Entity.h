#pragma once

#include <FrameMath/Vector2.h>
#include <FrameUtility/GUID.h>
#include <FrameEntity/ComponentRegister.h>

#include <unordered_map>

namespace Frame {
	
	typedef unsigned int EntityId;

	struct IEntityComponent;

	class CEntity {

	public:

		CEntity() = delete;
		CEntity(EntityId id)
			: m_id(id)
		{}
		virtual ~CEntity() {
			RemoveAllComponents();
		}

	private:

		const EntityId m_id;

		Vec2 m_vPosition { 0.f };
		Vec2 m_vScale { 1.f };

		// 弧度 | Radian
		float m_rotation = 0.f;

		// 主要用以表示遮挡关系（渲染顺序）
		// 数值越小，离镜头越近，渲染越晚
		// Mainly used to represent occlusion relationships (rendering order)
		// The smaller the value, the closer it is to the camera, and the later it renders
		int m_zDepth = 0;

	public:

		EntityId GetId() const { return m_id; }

		const Vec2 & GetPosition() const { return m_vPosition; }
		const Vec2 & GetScale() const { return m_vScale; }
		float GetRotation() const { return m_rotation; }
		int GetZDepth() const { return m_zDepth; }

		void SetPosition(const Vec2 & vPos) { m_vPosition = vPos; }
		void SetScale(const Vec2 & vScale) { m_vScale = vScale; }
		void SetRotation(float rotation) { m_rotation = rotation; }
		void SetZDepth(int zDepth) { m_zDepth = zDepth; }

		void Translate(const Vec2 & vPosAdd) {
			m_vPosition += vPosAdd;
		}

		void Scale(const Vec2 & vScaleMultiply) {
			m_vScale *= vScaleMultiply;
		}

		void Rotate(float rotAdd) {
			m_rotation += rotAdd;
		}

		template<typename ComponentType>
		ComponentType * CreateComponent() {
			ComponentType * pComponent = new ComponentType {};
			InitializeComponent_And_AddIntoProcessors(pComponent);

			m_components.insert(std::pair<GUID, IEntityComponent *> { SComponentType<ComponentType>::config.GetGUID(), pComponent });
			
			return pComponent;
		}

		template<typename ComponentType>
		ComponentType * GetComponent() {
			auto it = m_components.find(SComponentType<ComponentType>::config.GetGUID());
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
			if(auto it = m_components.find(SComponentType<ComponentType>::config.GetGUID()); it != m_components.end()) {
				RemoveComponent_And_RemoveFromProcessors(it->second);
				delete it->second;
				m_components.erase(it);
			}
		}

		void RemoveAllComponents();

	private:
		std::unordered_map<GUID, IEntityComponent *> m_components;
		
		void InitializeComponent_And_AddIntoProcessors(IEntityComponent * pComponent);
		void RemoveComponent_And_RemoveFromProcessors(IEntityComponent * pComponent);

	};

};