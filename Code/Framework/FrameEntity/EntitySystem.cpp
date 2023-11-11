﻿#include <FrameEntity/EntitySystem.h>

#include <FrameEntity/EntityEventProcessor.h>

namespace Frame {

	CEntitySystem::CEntitySystem() {
		using namespace EntityEvent;
		m_pEventProcessors[eEFI_Initialize]    = new CEntityEventProcessorImmediately { Initialize };
		m_pEventProcessors[eEFI_Update]        = new CEntityEventProcessor            { Update };
		m_pEventProcessors[eEFI_Render]        = new CEntityEventProcessorZSort       { Render };
		m_pEventProcessors[eEFI_Remove]        = new CEntityEventProcessorImmediately { Remove };
		m_pEventProcessors[eEFI_EnteredView]   = new CEntityEventProcessor            { EnteredView };
		m_pEventProcessors[eEFI_LeftView]      = new CEntityEventProcessor            { LeftView };
		m_pEventProcessors[eEFI_WindowResized] = new CEntityEventProcessor            { WindowResized };
	}
	
	CEntitySystem::~CEntitySystem() {
		for(Uint8 i = 0; i < EntityEvent::EFlagIndex::eEFI__END; i++) {
			delete m_pEventProcessors[i];
		}
	}

#define __ComponentDoSomethingAboutProcessors(__doWhat) \
	EntityEvent::Flags flags = pComponent->GetEventFlags(); \
	for(Uint8 i = 0; flags && i < EntityEvent::EFlagIndex::eEFI__END; i++) { \
		if(flags & 1) { \
			m_pEventProcessors[i]->__doWhat(pComponent); \
		} \
		flags >>= 1; \
	}

	void CEntitySystem::ComponentAddIntoProcessors(IEntityComponent * pComponent) {
		__ComponentDoSomethingAboutProcessors(Add);
	}

	void CEntitySystem::ComponentRemoveFromProcessors(IEntityComponent * pComponent) {
		__ComponentDoSomethingAboutProcessors(Remove);
	}

#undef __ComponentDoSomethingAboutProcessors

	void CEntitySystem::ProcessUpdateEvent() {
		// TODO - 帧耗时
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_Update]->Process();
	}

	void CEntitySystem::ProcessRenderEvent() {
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_Render]->Process();
	}

}