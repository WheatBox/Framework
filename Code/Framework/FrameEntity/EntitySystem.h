#pragma once

#include <FrameEntity/IEntity.h>
#include <FrameEntity/IEntityComponent.h>

#include <unordered_map>

namespace Frame {

	class CBaseEntityEventProcessor;

	typedef std::unordered_map<EntityId, IEntity *> EntitiesMap;
	
	class CEntitySystem {

	public:
		CEntitySystem();
		virtual ~CEntitySystem();

	private:
		EntitiesMap m_entities {};
		EntityId m_idNext = 0;

	public:

		IEntity * GetEntity(EntityId id) const {
			EntitiesMap::const_iterator it = m_entities.find(id);
			return (it == m_entities.end()) ? nullptr : it->second;
		}
		const EntitiesMap & GetEntities() const { return m_entities; }

		IEntity * SpawnEntity() {
			IEntity * p = new IEntity { m_idNext };
			if(p != nullptr) {
				m_entities[m_idNext++] = p;
			}
			return p;
		}

		void RemoveEntity(EntityId id) {
			EntitiesMap::iterator it = m_entities.find(id);
			if(it != m_entities.end()) {
				delete it->second;
				m_entities.erase(it);
			}
		}

		void ComponentAddIntoProcessors(IEntityComponent * pComponent);
		void ComponentRemoveFromProcessors(IEntityComponent * pComponent);

		void ProcessUpdateEvent();
		void ProcessRenderEvent();

	private:
		CBaseEntityEventProcessor * m_pEventProcessors[EntityEvent::EFlagIndex::eEFI__END];

	};

}