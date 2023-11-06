#pragma once

#include <FrameEntity/IEntity.h>

namespace Frame {

	class CBaseEntityEventProcessor;

	typedef std::unordered_map<EntityId, IEntity *> EntitiesMap;
	
	class CEntitySystem {

	public:
		CEntitySystem();
		virtual ~CEntitySystem() = default;

	private:
		EntitiesMap m_entities {};
		EntityId m_idNext = 0;

	public:

		IEntity * GetEntity(EntityId id) const {
			EntitiesMap::const_iterator it = m_entities.find(id);
			return (it == m_entities.end()) ? nullptr : it->second;
		}
		const EntitiesMap & GetEntities() const { return m_entities; }

		template<typename EntT>
		IEntity * SpawnEntity() {
			IEntity * p = new EntT { m_idNext };
			if(p != nullptr) {
				HandleEntityEventFlags(p);
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

		void HandleEntityEventFlags(IEntity * pEntity);

		void ProcessUpdateEvent();
		// void RenderEvent();

	private:
		CBaseEntityEventProcessor * m_pEventProcessors[EntityEvent::EFlagIndex::eEFI__END];

	};

}