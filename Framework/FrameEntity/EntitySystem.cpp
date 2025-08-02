#include "EntitySystem.h"

#include "../FrameEntity/EntityEventProcessor.h"

namespace Frame {

	CEntitySystem::CEntitySystem() {
		using namespace EntityEvent;
		m_pEventProcessors[eEFI_BeforeUpdate]  = new CEntityEventProcessor            { BeforeUpdate };
		m_pEventProcessors[eEFI_Update]        = new CEntityEventProcessor            { Update };
		m_pEventProcessors[eEFI_AfterUpdate]   = new CEntityEventProcessor            { AfterUpdate };
		m_pEventProcessors[eEFI_Render]        = new CEntityEventProcessorZSort       { Render };
		m_pEventProcessors[eEFI_EnteredView]   = new CEntityEventProcessor            { EnteredView };
		m_pEventProcessors[eEFI_LeftView]      = new CEntityEventProcessor            { LeftView };
		m_pEventProcessors[eEFI_WindowResized] = new CEntityEventProcessor            { WindowResized };
	}
	
	CEntitySystem::~CEntitySystem() {
		for(uint8 i = 0; i < EntityEvent::EFlagIndex::eEFI__END; i++) {
			delete m_pEventProcessors[i];
		}
	}

	void CEntitySystem::__ComponentAddIntoProcessors(IEntityComponent * pComponent) {
		m_addingComponents.push(pComponent);
	}

	void CEntitySystem::__ComponentRemoveFromProcessors(IEntityComponent * pComponent) {
		m_removingComponents.push(pComponent);
	}

	void CEntitySystem::__ProcessBeforeUpdateEvent() {
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_BeforeUpdate]->Process();
	}

	void CEntitySystem::__ProcessUpdateEvent() {
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_Update]->Process();
	}

	void CEntitySystem::__ProcessAfterUpdateEvent() {
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_AfterUpdate]->Process();
	}

	void CEntitySystem::__ProcessRenderEvent() {
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_Render]->Process();
	}

#define __ComponentDoSomethingAboutProcessors(__doWhat, pComponent) {\
	EntityEvent::Flags flags = pComponent->GetEventFlags(); \
	for(uint8 i = 0; flags && i < EntityEvent::EFlagIndex::eEFI__END; i++) { \
		if(flags & 1) { \
			m_pEventProcessors[i]->__doWhat(pComponent); \
		} \
		flags >>= 1; \
	} \
}

	void CEntitySystem::__AddAddingComponents() {
		while(!m_addingComponents.empty()) {
			auto p = m_addingComponents.front();
			m_addingComponents.pop();

			__ComponentDoSomethingAboutProcessors(Add, p);
			p->OnReady();
		}
	}

	void CEntitySystem::__RemoveRemovingEntitiesComponents() {
		for(const auto & pEntity : m_removingEntities) {
			pEntity->RemoveAllComponents();
		}
	}

	void CEntitySystem::__RemoveRemovingComponents() {
		while(!m_removingComponents.empty()) {
			auto p = m_removingComponents.front();
			m_removingComponents.pop();

			__ComponentDoSomethingAboutProcessors(Remove, p);

			p->OnShutDown();
			delete p;
		}
	}

#undef __ComponentDoSomethingAboutProcessors

	void CEntitySystem::__RemoveRemovingEntities() {
		for(const auto & pEntity : m_removingEntities) {
			delete pEntity;
		}
		m_removingEntities.clear();
	}

}