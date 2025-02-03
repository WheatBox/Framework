#pragma once

#include <FrameEntity/Entity.h>
#include <FrameEntity/IEntityComponent.h>

#include <unordered_map>

namespace Frame {

	struct IEntityEventProcessor;

	typedef std::unordered_map<EntityId, CEntity *> EntitiesMap;
	
	class CEntitySystem {

	public:
		CEntitySystem();
		virtual ~CEntitySystem();

	private:
		EntitiesMap m_entities {};
		EntityId m_idNext = 0;

	public:

		CEntity * GetEntity(EntityId id) const {
			EntitiesMap::const_iterator it = m_entities.find(id);
			return (it == m_entities.end()) ? nullptr : it->second;
		}
		const EntitiesMap & GetEntities() const { return m_entities; }

		CEntity * SpawnEntity() {
			CEntity * p = new CEntity { m_idNext };
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

		void ProcessBeforeUpdateEvent(float frameTime);
		void ProcessUpdateEvent(float frameTime);
		void ProcessAfterUpdateEvent(float frameTime);
		void ProcessRenderEvent();

	private:
		IEntityEventProcessor * m_pEventProcessors[EntityEvent::EFlagIndex::eEFI__END];

	};

}

#include <FrameEntity/ComponentRegister.h>
