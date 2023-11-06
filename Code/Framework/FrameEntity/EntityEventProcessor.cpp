#include <FrameEntity/EntityEventProcessor.h>

#include <FrameEntity/IEntity.h>

namespace Frame {

	void CEntityEventProcessor::Process() {
		for(auto pEntity : m_set) {
			pEntity->ProcessEvent(m_event);
		}
	}
	
	void CEntityEventProcessor::Join(IEntity * pEntity) {
		m_set.insert(pEntity);
	}

	void CEntityEventProcessor::Remove(IEntity * pEntity) {
		auto it = m_set.find(pEntity);
		if(it != m_set.end()) {
			m_set.erase(it);
		}
	}

	void CEntityEventProcessorZSort::Process() {
	}

	void CEntityEventProcessorZSort::Join(IEntity * pEntity) {
		pEntity;
	}

	void CEntityEventProcessorZSort::Remove(IEntity * pEntity) {
		pEntity;
	}

}