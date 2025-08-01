#pragma once

#include "../FrameEntity/Entity.h"
#include "../FrameEntity/IEntityComponent.h"

#include <unordered_map>
#include <queue>

namespace Frame {

	struct IEntityEventProcessor;

	typedef std::unordered_map<EntityId, CEntity *> EntitiesMap;
	
	class CEntitySystem {

	public:
		CEntitySystem();
		virtual ~CEntitySystem();

	private:
		EntitiesMap m_entities {};
		EntityId m_idNext = 1;

	public:

		CEntity * GetEntity(EntityId id) const {
			EntitiesMap::const_iterator it = m_entities.find(id);
			return (it == m_entities.end()) ? nullptr : it->second;
		}
		const EntitiesMap & GetEntities() const { return m_entities; }

		// m_entities 没有相关轮询，所以为立即执行
		CEntity * SpawnEntity() {
			CEntity * p = new CEntity { m_idNext };
			if(p != nullptr) {
				m_entities[m_idNext++] = p;
			}
			return p;
		}

		// 因为要清除实体内的组件，所以需要延迟执行
		void RemoveEntity(CEntity * pEntity) {
			if(pEntity) {
				pEntity->RemoveAllComponents();
				m_removingEntities.push(pEntity->GetId());
			}
		}
		// 因为要清除实体内的组件，所以需要延迟执行
		void RemoveEntity(EntityId id) {
			RemoveEntity(GetEntity(id));
		}

		void __ComponentAddIntoProcessors(IEntityComponent * pComponent);
		void __ComponentRemoveFromProcessors(IEntityComponent * pComponent);

		void __ProcessBeforeUpdateEvent();
		void __ProcessUpdateEvent();
		void __ProcessAfterUpdateEvent();
		void __ProcessRenderEvent();

		void __AddAddingComponents();
		void __RemoveRemovingComponents();
		void __RemoveRemovingEntities();

	private:
		IEntityEventProcessor * m_pEventProcessors[EntityEvent::EFlagIndex::eEFI__END];
		
		std::queue<IEntityComponent *> m_addingComponents;
		std::queue<IEntityComponent *> m_removingComponents;
		std::queue<EntityId> m_removingEntities;
	};

}

#include "../FrameEntity/ComponentRegister.h"
