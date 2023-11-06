#include <FrameEntity/EntitySystem.h>

#include <FrameEntity/EntityEventProcessor.h>

namespace Frame {

	CEntitySystem::CEntitySystem() {
		using namespace EntityEvent;
		m_pEventProcessors[eEFI_Initialize] = new CEntityEventProcessor { Initialize };
		m_pEventProcessors[eEFI_Update] = new CEntityEventProcessor { Update };
		m_pEventProcessors[eEFI_Render] = new CEntityEventProcessorZSort { Render };
		m_pEventProcessors[eEFI_Remove] = new CEntityEventProcessor { Remove };
		m_pEventProcessors[eEFI_EnteredView] = new CEntityEventProcessor { EnteredView };
		m_pEventProcessors[eEFI_LeftView] = new CEntityEventProcessor { LeftView };
		m_pEventProcessors[eEFI_WindowResized] = new CEntityEventProcessor { WindowResized };
	}

	void CEntitySystem::HandleEntityEventFlags(IEntity * pEntity) {
		Frame::EntityEvent::Flags flags = pEntity->GetEventFlags();
		for(Uint8 i = 0; flags && i < Frame::EntityEvent::EFlagIndex::eEFI__END; i++) {
			if(flags & 1) {
				m_pEventProcessors[i]->Join(pEntity);
			}
			flags >>= 1;
		}
	}

	void CEntitySystem::ProcessUpdateEvent() {
		// TODO - 帧耗时
		m_pEventProcessors[EntityEvent::EFlagIndex::eEFI_Update]->Process();
	}

}